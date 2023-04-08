import datetime 

def check_date_form(date : str):
    try:
        datetime.datetime.strptime(date, '%Y%m%d')
    except:
        return False
    return True

if __name__ == '__main__':
    print(type(datetime.datetime.strptime('20220303', '%Y%m%d')))