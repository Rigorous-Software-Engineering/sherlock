from pycparser import c_ast

def add_param_lvars(ast, lvars_list):
    v = Visitor(lvars_list)
    v.visit(ast)

def get_param_names(param_l):
    res = set()
    for param in param_l:
        if isinstance(param.name, str):
            # for ArrayDecl add as expression name arr[0]
            if isinstance(param.type, c_ast.ArrayDecl):
                res.add(param.name + '[0]')
            else:
                res.add(param.name)
    return res

class Visitor(c_ast.NodeVisitor):
    def __init__(self, lvars_list):
        self.lvars_list=lvars_list

    def visit_FuncDef(self, node):
        # ensure that FuncDef is from the original C-File and not from a header file
        if node.coord.file.endswith('.c'):
            decl = node.decl
            if decl.name != 'main':
                param_l = decl.type.args
                # check if there are parameters
                if param_l is not None:
                    params = get_param_names(param_l)
                    items = node.body.block_items
                    # ensure that function body is none-empty
                    if items is not None:
                        line_start = items[0].coord.line
                        line_end = items[len(items) - 1].coord.line
                        for line_nr in range(line_start, line_end):
                            self.lvars_list[line_nr].update(params)