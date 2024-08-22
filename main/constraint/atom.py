import copy

from .form import FormInterface
import constraint.bin_constraint as bin_constraint


class Atom(FormInterface):

    def __init__(self, s_vars, c_vars, code_constants, is_symbolic, form_tps):
        FormInterface.__init__(self,s_vars,c_vars, code_constants, form_tps)
        if is_symbolic:
            vars1 = sorted(s_vars)
            vars2 = sorted(c_vars)
        else:
            vars1 = sorted(s_vars) + sorted(c_vars)
            vars2 = []
        self.bin_constraint = bin_constraint.new_binary_constraint(vars1, vars2, code_constants)

    def weaken(self):
        # copy
        new_atom = copy.copy(self)
        # and weaken underlying constraint
        new_atom.bin_constraint = self.bin_constraint.weaken()
        return new_atom, None

    def __str__(self):
        return str(self.bin_constraint)

    def strengthen(self):
        # copy
        new_atom = copy.copy(self)
        # and weaken underlying constraint
        new_atom.bin_constraint = self.bin_constraint.strengthen()
        return new_atom, None # second param should be thrown away in compound.py