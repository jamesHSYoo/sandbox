from dateutil.parser import parse
import util.util

class Animal():
    def __init__(self, species, name, birth_day):
        self.species = species
        self.__name = name   # 접근 제어자 -> 이 경우 필드를 보여줄 땐 getter, setter 함수를 만들 필요가 있음
        try:
            self.birth_day = parse(birth_day)
        except :
            raise Exception("birth day type is not available.") 
        print("Success to create instance")
    def to_string(self):
        print("Species : " + self.species + 
              "\nName : " +self.__name +
              "\nBirth Day : " + self.birth_day.strftime("%Y%m%d"))
    def say_species(self):
        print(self.species)
    def say_name(self):
        return self.__name

if __name__ == "__main__":
    test_instance = Animal("Horse", "James","19900227")
    test_instance.to_string()
    print(test_instance.say_name())

    print(util.util.get_now_time())