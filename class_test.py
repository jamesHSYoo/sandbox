from dateutil.parser import parse

class Animal():
    def __init__(self, species, birth_day):
        self.species = species
        try:
            self.birth_day = parse(birth_day)
        except :
            raise Exception("birth day type is not available.") 
        print("Success to create instance")
    def to_string(self):
        print("Species : " + self.species + "\nBirth Day : " + self.birth_day.strftime("%Y%m%d"))
    def say_species(self):
        print(self.species)

if __name__ == "__main__":
    test_instance = Animal("Horse", "19900227")
    test_instance.to_string()