import requests
# filename cannot be 'html.py' which will lead to conflict to bs!!
from bs4 import BeautifulSoup
import csv


# Get raw html info
def get_html_info(url):
    try:
        print('url:'+url)
        re = requests.get(url, timeout=30)
        re.raise_for_status()
        re.encoding = 'utf-8'
        print("Get raw info.")
        return re.text
    except:
        print("[Error] Failed to get HTML info!")


# Save raw html info to the file
def save_html_info(html_info):
    file = open('raw_html_info.txt', 'w')
    for info in html_info:
        file.write(info)
    file.close()
    print("Saved raw info to the file.")


# Re raw html info from the list
def re_html_info(raw_html_info):
    # Using bs4 to extract raw info
    soup = BeautifulSoup(raw_html_info, 'html.parser')
    data = soup.find_all('tr')
    # print(data)  # test
    ready_info = []
    i = 0
    for info in data:
        if i < 2:
            # escape the title
            i += 1
            continue
        else:
            info = str(info)
            re_info = {}
            # Save serial numbers to list
            serial_num_start = info.find(
                '; height: 18.75pt">')
            serial_num_end = info.find('</td>')
            serial_num = info[serial_num_start+19: serial_num_end]
            re_info['序号'] = serial_num  # " ".join(serial_num.split())

            # Save student names to list
            student_name_start = info.find(
                'left: medium none">', serial_num_end, len(info))
            student_name_end = info.find('</td>', student_name_start, len(info))
            student_name = info[student_name_start+19: student_name_end]
            re_info['姓名'] = student_name  # " ".join(student_name.split())

            # Save school names to list
            school_name_start = info.find(
                'left: medium none">', student_name_end, len(info))
            school_name_end = info.find('</td>', school_name_start, len(info))
            school_name = info[school_name_start+19: school_name_end]
            re_info['录取学校'] = school_name  # " ".join(school_name.split())

            # Save school types to list
            school_types_start = info.find(
                'left: medium none">', school_name_end, len(info))
            school_types_end = info.find('</td>', school_types_start, len(info))
            school_types = info[school_types_start+19: school_types_end]
            re_info['大学类型'] = school_types  # " ".join(school_types.split())

            ready_info.append(re_info)
    print("Info is ready.")
    return ready_info


def save_to_csv(ready_info):
    with open('re_html_info.csv', 'wt', encoding='utf-16') as csvfile:
        csvout = csv.DictWriter(csvfile, ['序号', '姓名', '录取学校', '大学类型'])
        csvout.writeheader()
        csvout.writerows(ready_info)
    print("Save to csv.")


def main():
    url = 'http://www.sszx.cn/jxjy/xkjs/201802/t20180205_8967.htm'
    raw_html_info = get_html_info(url)  # Get raw html info
    save_html_info(raw_html_info)  # Save raw html info to file
    ready_info = re_html_info(raw_html_info)  # re raw html info from file
    print(ready_info)
    save_to_csv(ready_info)  # Save ready info to csv


if __name__ == '__main__':
    main()
