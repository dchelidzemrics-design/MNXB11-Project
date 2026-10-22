import csv 

# The parsed data will end up in a list. All entries in the raw data 
# that has a quality 'Y' will be removed. We also ignore the minutes and seconds
# of the temperature reading. 
parsed_data = [['year', 'month', 'day', 'hour', 'temperature']]

# Function that flattens a list of lists
def flatten(lists):
    
    flat_list = []

    for l in lists:
        for item in l:
            flat_list.append(item)

    return flat_list

# Open original Data.csv file 
with open('datasets/Data.csv') as f:
    data = csv.reader(f)
    for row in data:

        # Only keep datapoints that has quality 'G'.
        # The strip method removs leading and ending whitespaces
        if str(row[3]).strip() == 'G':

            # The int(i) will remove leading zeros
            date = [int(i) for i in row[0].split('-')]
            time = [int(i) for i in row[1].split(':')]
            temp = [float(row[2])]

            # We only keep the hour reading of the time of observation
            parsed_data_row = [date, [time[0]], temp]
            parsed_data.append(flatten(parsed_data_row))

# Save the parsed data as a .csv file in the datasets directory
with open('datasets/ParsedData.csv', 'w', newline='') as f:
    w = csv.writer(f)
    w.writerows(parsed_data)