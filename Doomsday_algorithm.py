from random import randint
import time, os, sys

months = ["Poop", "Jan", "Feb", "March", "April", "May", "June", "July", "August", "Sep","Oct", "Nov", "Dec"]
thirty1 = ["Jan", "March", "May", "July", "August", "Oct", "Dec"]
centuryDay = [2, 7, 5, 3]
doomsDays = [20000000, 3, 28, 14, 4, 9, 6, 11, 8, 5, 10, 7, 12]

print("Give your answer in number of the day of the week:")
print("1 = Monday, 2 = Tuesday, 3 = Wednesday, 4 = Thursday, 5 = Friday, 6 = Saturday, 0 = Sunday")

year = 0
day = 0

times = []
ao5 = []
ao12 = []

count = 0

while (1):
    count += 1
    year = randint(1700,2050)
    if (year % 4 == 0):
        doomsDays[1:3] = [4, 29]
    monthNo = randint(1,12)
    month = months[monthNo]
    
    if month in thirty1:
        day = randint(1,31)
    else:
        if (month == "Feb"):
            if (year % 4 == 0):
                day = randint(1,29)
            else:
                day = randint(1,28)
        else:
            day = randint(1,30)


    print("What is the day of the week on " + str(month) + " " + str(day) + ", " + str(year) + "?")
    time1 = time.time()

    century = centuryDay[(year // 100) % 4]
    doubleYear = (year % 100) % 28
    yearDoom = (((doubleYear+(doubleYear // 4)) % 7)+century) % 7
    ans = yearDoom

    if (day == doomsDays[monthNo]):
        ans += 0
    else:
        ans += day - (doomsDays[monthNo]%7)
    if (ans < 0):
        ans += 7

    ans = str(ans%7)
    been_wrong = 0
    while (1):
        s = input()
        if not been_wrong:
            sys.stdout.write("\033[F")  
            sys.stdout.write("\033[K")  
        if (s == ans):
            time2 = time.time()
            duration = int((time2-time1)*100)/100
            times.append(duration)
            print("Yay! You got it in " + str(duration) + " seconds!")
            print("Current session mean: " + str(sum(times)/len(times)) + " seconds.")
            if count >= 5:
                cAo5 = int(100*sum(times[-5:])/5)/100
                print("Current average of 5: " + str(cAo5))
                ao5.append(cAo5)
            if count >= 12:
                cAo12 = int(100*sum(times[-12:])/12)/100
                print("Current average of 12: " + str(cAo12))
                ao12.append(cAo12)
            if count%10 == 0:
                print("Times played: " + str(count))
            break

        if been_wrong:
            for _ in range(4):
                sys.stdout.write("\033[F")  
                sys.stdout.write("\033[K")  
        print(s)
        print("You are wrong. Try again.")
        print("Remember to give your answer in the form mentioned above.")
        been_wrong = 1

    doomsDays[1:3] = [3, 28]
    print("Type any key to continue or 'stop' to stop the session")
    query = input()
    if (query == "stop"):
        print("Thank you for playing.")
        print("Best time: ", min(times))
        if count >= 5:
            print("Best average of 5: ", min(ao5))
        if count >= 12:
            print("Best average of 12: ", min(ao12))
        print(input("Press any key to stop"))
        break
