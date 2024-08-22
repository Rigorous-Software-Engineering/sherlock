from .form import FormInterface


class ConstraintBuilder:

    def __init__(self, symbolic_constraints_only, form_tps):
        self.require_symbolic = symbolic_constraints_only
        self.form_tps = form_tps

    # requires 'symbolic_vars + concrete_vars' to be non-empty
    def new_constraint(self, symbolic_vars, concrete_vars, f_ctx):
        # cannot create a symbolic constraint if there is no symbolic variable
        # should not/cannot create a (concrete) constraint if there is no variable at all
        if len(symbolic_vars) == 0 and (self.require_symbolic or len(concrete_vars) == 0):
            return None
        return FormInterface(symbolic_vars,concrete_vars,f_ctx, self.form_tps).get_random_form(self.require_symbolic, allow_atoms=False)