
''' Replace class with dictionary
class   person:
    def __init__(self, name, age, role):
        self.name = name
        self.role = role
        self.age = age
'''

def printTable(db):
    for i in db:
        print(f'LoginId : {i}\t')
        for j in db[i]:
            print(f"{j} : {db[i][j]},", end='\t')
        print()

if __name__ == "__main__":

    john = {'name':'John', 'age':25, 'role':'adm'}
    paul = {'name':'Paul', 'age':33, 'role':'ceo'}
    wanda = {'name':'Wanda', 'age':50, 'role':'engr'}
    eric = {'name':'Eric Johnson', 'age':70, 'role':'sw'}
    george = {'name':'George', 'age':52, 'role':'hw'}
    jerome = {'name':'Jerome Beckman', 'age':43, 'role':'carpenter'}
    judy = {'name':'Judy Miller', 'age':61, 'role':'cashier'}
    jose = {'name':'Jose Sanchez', 'age':66, 'role':'gardener'}
    kevin = {'name':'Kevin Wolfe', 'age':37, 'role':'security'}
    robert = {'name':'Robert', 'age':70, 'role':'technician'}
    jane = {'name':'Jane Rutherford', 'age':44, 'role':'secretary'}

    # hashTableSize = 5
    dict_db = {'john_s' : john, 'paul_k' : paul, 'wanda_m' : wanda, 'eric_j' : eric,
                  'george_h' : george, 'jerome_b' : jerome, 'judy_m' : judy,
                  'jose_s' : jose, 'kevin_w' : kevin, 'robert_o' : robert, 'jane_r' : jane}

    print(f"\nThere are {len(dict_db)} person objects in this dictionary database")
    printTable(dict_db)

    name = input("What is your login id? 'nil' to end : ")
    while (name != 'nil'):
        if (name in dict_db):
            print(f"\t{name} Found -> {dict_db[name]}")
        else:
            print(f'\tloginId {name} is non-existent!')
        name = input("Whom are you looking for? ")

    name = input("Login Id of the person to remove, 'nil' to end : ")
    while (name != 'nil'):
        if (name in dict_db):
            person = dict_db.pop(name)
            print(f"\t{person} has been deleted.")
        else:
            print(f'\tloginId {name} is non-existent!')
        name = input("Login Id of the person to remove : ")

    printTable(dict_db)



