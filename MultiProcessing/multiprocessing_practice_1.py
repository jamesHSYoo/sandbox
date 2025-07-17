import time
import multiprocessing

def do_someting():
    print('1초간 잠듭니다.')
    time.sleep(1)
    print("Wake up!")

if __name__ == '__main__':
    do_someting()