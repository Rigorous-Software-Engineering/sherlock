import re

from pycparser import c_ast

""" This class parses a C-File with pycparser library and extracts information about the type of the value (storing 
this info in a dict) and information about whether a variable is (likely) symbolic"""

def __is_symbolic_fnc_call__(node):
    if isinstance(node, c_ast.FuncCall):
        nm = node.name
        return isinstance(nm, c_ast.ID) and nm.name.startswith("__VERIFIER_nondet_")


def __is_tp_numeric__(tp):
    if isinstance(tp, c_ast.ArrayDecl):
        type_obj = tp.type
    # otw. the object shall immediately be a TypeDecl object if 'variable' defines a numeric primitive variable
    else:
        type_obj = tp
    if isinstance(type_obj, c_ast.TypeDecl) and isinstance(type_obj.type, c_ast.IdentifierType):
        numeric_keywords_re = ['char','signed','int.*','uint.*', 'long', 'float', 'double','unsigned', 'short']
        type_names = type_obj.type.names
        for keywords_re in numeric_keywords_re:
           for type_name in type_names:
               if re.fullmatch(keywords_re, type_name):
                   return True
    else:
        return False


class TypeExtractor:
    def __init__(self, ast):
        v = self.Visitor()
        v.visit(ast)
        self.numeric_vars = v.numeric_vars
        self.symbolic_vars = v.symbolic_set
        self.numeric_constants = sorted(v.numeric_constants)

    class Visitor(c_ast.NodeVisitor):
        def __init__(self):
            self.numeric_vars = set()
            self.symbolic_set = set()
            self.numeric_constants = set()

        def visit_Decl(self, node):
            # if Decl declares a function, add all the function parameter declarations
            if isinstance(node.type, c_ast.FuncDecl):
                self.handle_fnc_decl(node)
            # otherwise Decl declares some data element (variable, pointer or array)
            else:
                self.handle_data_decl(node)
            self.generic_visit(node)

        # handles declarations of data elements (= no functions)
        def handle_data_decl(self, data_decl_node):
            # check if 'data_decl_node' declares a symbolic variable
            init = data_decl_node.init
            name = data_decl_node.name
            if __is_symbolic_fnc_call__(init):
                self.symbolic_set.add(name)
            # check the type of 'data_decl_node', i.e. if it declares a numeric variable
            tp = data_decl_node.type
            if __is_tp_numeric__(tp):
                self.numeric_vars.add(name)
            # in case the variable is already defined as numeric - undo this
            # WARNING: this is unsafe: It might be that the numeric declaration is traversed in the end
            elif name in self.numeric_vars:
                self.numeric_vars.remove(name)

        def handle_fnc_decl(self, fnc_decl_node):
            tp = fnc_decl_node.type
            if tp.args is not None:
                for param in tp.args.params:
                    if isinstance(param, c_ast.Decl):
                        self.handle_data_decl(param)

        def visit_Assignment(self, node):
            if isinstance(node.lvalue, c_ast.ArrayRef):
                # possibly mark the whole array as symbolic (unsound), use the nested (possible) ID object
                lhs = node.lvalue.name
            else:
                lhs = node.lvalue
            if isinstance(lhs, c_ast.ID) and __is_symbolic_fnc_call__(node.rvalue):
                self.symbolic_set.add(lhs.name)
            self.generic_visit(node)

        def visit_Constant(self, node):
            if 'int' in node.type:
                self.numeric_constants.add(node.value) # notice that node.value is a string (e.g. node.value=='2u')
            self.generic_visit(node)


    # check if variable (which is either variable name or array reference name is numeric or not)
    def is_numeric(self, variable):
        if '[' in variable:
            variable = variable.split('[')[0]
        return variable in self.numeric_vars


# expr might be a primitive variable or an array reference
    def is_symbolic(self, expr):
        array_match_res = re.match('([_a-zA-Z][_a-zA-Z0-9]*) *(\[.*\])+', expr)
        if array_match_res is not None:
            variable = array_match_res.group(1)
        else:
            variable = expr
        return variable in self.symbolic_vars

    def get_constants(self):
        return self.numeric_constants

