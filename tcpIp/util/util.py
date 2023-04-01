import datetime

def diff_two_time(_begin_date, _end_date):
    
    begin_date = datetime.datetime.strptime(_begin_date, '%Y%m%d')
    end_date = datetime.datetime.strptime(_end_date, '%Y%m%d')

    return (end_date - begin_date).days