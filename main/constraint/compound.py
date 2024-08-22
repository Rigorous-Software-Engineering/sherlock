from .form import FormInterface


class CompoundInterface(FormInterface):
    def __init__(self, s_vars, c_vars, f_ctx, op_symbol, form_tps):
        FormInterface.__init__(self,s_vars,c_vars, f_ctx, form_tps)
        self.operator_symbol = op_symbol # Initialize me in a subclass
        self.forms = []

    def __weaken__forms__(self) -> list:
        return list(map(lambda f : f.weaken()[0], self.forms))

    def __strengthen__forms__(self) -> list:
        return list(map(lambda f : f.strengthen()[0], self.forms))

    def __str__(self):
        return '(' + (' ' + self.operator_symbol + ' ').join(map(str,self.forms)) + ')'