import csv
import numpy
import time
from apyori import apriori

FILENAME = '../data/groceries.csv'
DATA = []
MIN_SUPPORT = 0.01
MIN_CONFIDENCE = 0.4
MIN_LIFT = 3


with open(FILENAME, newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    for row in spamreader:
        DATA.append(row)
for min_support in numpy.arange(0.004, 0.013, 0.002):
    start_time = time.time()
    print("#################################################")
    association_rules = apriori(DATA, min_support=min_support, min_confidence=MIN_CONFIDENCE, min_lift=MIN_LIFT)
    association_results = list(association_rules)
    for item in association_results:
        pair = item[0]
        items = [x for x in pair]
        print("Frequent Set: ", ",".join(item.items))
        print("Rule: " + items[0] + " -> " + items[1])
        print("Support: ", item[1])
        print("Confidence: ", item[2][0][2])
        print("Lift: ", item[2][0][3])
        print("=====================================")
    end_time = time.time()
    relation_record_num = len(association_results)
    _time = end_time - start_time
    print("**** Current min_support:", min_support, "Current min_confidence:", MIN_CONFIDENCE, " ****")
    print("**** Number of RelationRecord: ", str(relation_record_num), " Time: ",
          str(_time), " Efficiency: ", str(relation_record_num/_time), " ****")
