import book_study.els_step_down_book.FDM.els_stepdown_1_asset_fdm as one_asset
import book_study.els_step_down_book.FDM.els_stepdown_2_asset_fdm as two_asset
import book_study.els_step_down_book.FDM.els_stepdown_3_asset_fdm as three_asset

from common.person import Person

def execute():
    print("1 Asset : %f" % one_asset.calculate_one_asset())
    print("2 Asset : %f" % two_asset.calculate_two_asset())
    print("3 Asset : %f" % three_asset.calculate_three_assets())


if __name__ == '__main__':
    # a = Util()
    # a.display_my_ip()
    a = Person()
    a.set_person("James", "32", "01077661479", "Seoul")
    print(a.get_name)