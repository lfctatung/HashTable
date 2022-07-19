
class   person:
    def __init__(self, name, age, role):
        self.name = name
        self.role = role
        self.age = age


class   hastTable:
    def __init__(self, size):
        self.ht = []
        self.size = size
        for i in range(size):
            self.ht.append([])

    def hash(self, name):
        v = 0
        i = 0
        for c in name:
            v += ord(c) << i
            i += 1
        return v % self.size

    def insert(self, p):
        index = self.hash(p.name)
        print(f"hashTable insert '{p.name}' to index {index}")
        # add an item to the end of the list
        self.ht[index].append(p)
        # self.ht[index] += [p]

    def lookup(self, name):
        index = self.hash(name)
        for person in   self.ht[index]:
            if person.name == name:
                print(f"\tFound {name} in hash index {index}")
                return True
        print(f"\t{name} Not Found")

    def delete(self, name):
        index = self.hash(name)
        length = len(self.ht[index])
        deleted = False
        if length == 0:
            print(f"\thashTable delete '{name}' from index {index} : Empty list")
        else:
            print(f"\thashTable delete '{name}' from index {index} with list length = {length}")
            for i in range(length):
                if self.ht[index][i].name == name:
                    # self.ht[index][i] = []  #   replaced by [], but still count as an entry, but empty, not a person object
                    self.ht[index].pop(i)
                    deleted = True
                    break
            if deleted == False:
                print(f"\thashTable delete '{name}' from index {index} : Not Found, i.e. Not inserted yet!")
        return deleted

    def printTable(self):
        for i in range(hashTableSize):
            print(f"index {i} : ", end=" ")
            for j in range(len(self.ht[i])):
                print(f"{self.ht[i][j].name}", end=", ")
            print()

'''
>>> a = list(x**2 for x in range(6))
>>> a
[0, 1, 4, 9, 16, 25]
>>> a[2:4]=[-1,-2,-3]   //  change a[2, 3]
>>> a
[0, 1, -1, -2, -3, 16, 25]
>>> a[4:5]=[]   //  remove a[4]
>>> a
[0, 1, -1, -2, 16, 25]
>>> a[3:5]=[]   //  remove a[3, 4]
>>> a
[0, 1, -1, 25]

>>> a = [[1,5,6,8,20],[1,2,5,9],[7,5,6]]
>>> len(a)
3
>>> len(a[0])
5
'''

if __name__ == "__main__":

    john = person('John', 25, 'adm')
    paul = person('Paul', 33, 'ceo')
    wanda = person('Wanda', 58, 'engr')
    eric = person("Eric Johnson", 70, 'sw')
    george = person("George", 52, 'hw')
    jerome = person("Jerome Beckman", 43, 'carpenter')
    judy = person("Judy Miller", 61, "cashier")
    jose = person("Jose Sanchez", 66, "gardener")
    kevin = person("Kevin Wolfe", 37, 'security')
    robert = person("Robert", 70, 'technician')
    jane = person("Jane Rutherford", 44, "secretary")

    hashTableSize = 5
    tp_db = (john, paul, wanda, eric, george, jerome, judy, jose, kevin, robert, jane)
    print(f"\nThere are {len(tp_db)} person objects in this tuple database")
    hashT = hastTable(hashTableSize)
    for person in tp_db:
        hashT.insert(person)
    hashT.printTable()

    name = input("Whom are you looking for? 'nil' to end : ")
    while (name != 'nil'):
        hashT.lookup(name)
        name = input("Whom are you looking for? ")

    name = input("Name of the person to remove, 'nil' to end : ")
    while (name != 'nil'):
        if (hashT.delete(name) == True):
            print(f"\t{name} has been deleted.")
        else:
            print(f'\t{name} is non-existent!')
        name = input("Name of the person to remove : ")

    hashT.printTable()


