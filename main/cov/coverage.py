def get_coverage_str(s):
    res = ''
    for loc_nr in s.assertions_dict:
        if s.has_failing_assertions_at(loc_nr):
            res+='1'
        else:
            res+='0'
    return res
