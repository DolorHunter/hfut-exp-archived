import csv


# Count school and schooltypes
def count(schooltimes, schooltypestimes, schooltimes_list, schooltypestimes_list):
    with open('re_html_info.csv', 'rt', encoding='utf-16') as csvfile:
        reader = csv.DictReader(csvfile)

        for row in reader:
            # Count school
            for school in row['录取学校'].split():
                if school in schooltimes.keys():
                    schooltimes[school] += 1
                else:
                    schooltimes[school] = 1

            # Count school type
            for schooltypes in row['大学类型'].split():
                if schooltypes in schooltypestimes.keys():
                    schooltypestimes[schooltypes] += 1
                else:
                    schooltypestimes[schooltypes] = 1

    # Sort
    schooltimes_list.extend(list(schooltimes.items()))
    schooltypestimes_list.extend(list(schooltypestimes.items()))
    schooltimes_list.sort(key=lambda x: x[1], reverse=True)
    schooltypestimes_list.sort(key=lambda x: x[1], reverse=True)
    for tuples, i in zip(schooltimes_list, range(1, 999)):
        print('School---No.'+str(i), tuples)
    for tuples, i in zip(schooltypestimes_list, range(1, 999)):
        print('Schooltypes---No.'+str(i), tuples)


def main():
    count(schooltimes, schooltypestimes, schooltimes_list, schooltypestimes_list)


schooltimes = {}
schooltypestimes = {}
schooltimes_list = []
schooltypestimes_list = []


if __name__ == '__main__':
    main()

