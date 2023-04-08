import datetime
import dataclasses

class SchduleClassic:
    begin_date = datetime.datetime.strptime('19000101', '%Y%m%d')
    end_date = datetime.datetime.strptime('19000101', '%Y%m%d')
    reset_date = datetime.datetime.strptime('19000101', '%Y%m%d')
    settle_date = datetime.datetime.strptime('19000101', '%Y%m%d')

    def __init__(self, _begin_date : str, _end_date : str, _settle_date : str, _reset_date : str = ''
    ) -> None:
        self.begin_date = datetime.datetime.strptime(_begin_date, '%Y%m%d')
        self.end_date = datetime.datetime.strptime(_end_date, '%Y%m%d')
        self.settle_date = datetime.datetime.strptime(_settle_date, '%Y%m%d')
        if _reset_date != '':
            self.reset_date = datetime.datetime.strptime(_reset_date, '%Y%m%d')

@dataclasses
class CouponSchdule:
    begin_date : datetime.datetime
    end_date : datetime.datetime
    settle_date : datetime.datetime
    reset_date : datetime.datetime = datetime.datetime.strptime('19000101', '%Y%m%d')