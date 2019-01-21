class Kamus:
    
    def __init__(self, word=''):

        
        if word == '':
            self.left = None
            self.right = None
            self.data = None
        
        elif len(word) == 1:
            self.left = None
            self.right = None
            self.data = word
        
        else:
            self.right = None
            self.data = word[0]
            self.left = Kamus(word[1:]) 

    def add(self, word):
        if ord(word[0]) > ord(self.data):
            if self.right is None:
                self.right = Kamus(word)
            else:
                self.right.add(word)
        elif ord(word[0]) < ord(self.data):
            right = self.right
            left = self.left

            self.right = Kamus(self.data)
            self.left = Kamus(word[1:])
            self.data = word[0]

            self.right.left = left
            self.right.right = right
        else:
            # if len(word[1:]) > 1:
            if self.left is None:
                self.left = Kamus(word[1:])
            else:
                self.left.add(word[1:])
            # else:
            #     self.left = Kamus(word[1:])

    def getDeep(self):
        deep = 0
        while self.right:
            deep += 1
            self = self.right
        return deep
    
    def printKamus(self, deep = 0):

        print(self.data, end='')
        
        # if self.left is None:
        #     print(' '+str(deep), end='')

        if self.left:
            deep += 1
            print('-',end='')
            self.left.printKamus(deep)
            deep -= 1
            
        # if self.left:
        #     deep = self.getDeep()

        if self.right:

            print()

            # if deep != 0:
            #     print('|', end='')
            #     for i in range((deep-1)*2 +1):
            #         print(' ', end='')
            
            if deep != 0:
                for i in range(deep):
                    print('  ', end='')

            print('|')

            
            # if deep != 0:
            #     print('|', end='')
            #     for i in range((deep-1)*2 +1):
            #         print(' ', end='')

            if deep != 0:
                for i in range(deep):
                    print('  ', end='')
            
            self.right.printKamus(deep)
    
    def print(self):
        self.printKamus()
        print()
    
    def search(self, keyWord):

        print('\nMemulai pencarian \''+keyWord+'\'...\n')

        lenKeyword = len(keyWord)
        
        ketemu = False

        for i in range(lenKeyword):

            if keyWord[i] == self.data:
                # print('kiri')
                self = self.left

            elif ord(keyWord[i]) > ord(self.data) and self.right != None:
                # print('kanan')
                self = self.right
                while self.data != keyWord[i] and self.right != None:
                    self = self.right
                if self.data == keyWord[i]:
                    self = self.left
                    
            
            if i == lenKeyword-1:
                ketemu = True
                matchWord = []
                tree2word(self, matchWord, 0)


        if ketemu:
            print('\''+keyWord + '\' ditemukan')
            print('kata yang mungkin terkait: ')
            return [ keyWord + x for x in matchWord]

        else:
            return 'Pencarian tidak ditemukan'

            
            
            




        
# #     def search(self, keyWord):
        
# #         tree = self
# #         ayam = Kamus()
# #         # print(tree.data, tree.left.data)
        
# #         for char in keyWord:
            
# #             # print(tree.data)
# #             print(char + ' ' + tree.data)

# #             ayam = find(tree, char)
# #             # print(tree.left.data + ' ' + tree.data + ' ' +tree.right.data)
# #             print (ayam)

# #             # print(char + ' ' + tree.data)
# #             #     # print('pindah' + tree.data)
# #             #     tree = tree.left
# #             # else:
# #                 # return "kata tidak diteanss"
        
# #         matchWord = []

# #         # print("data tree " + tree.data)
# #         tree2word(tree, matchWord, 0)
            
# #         return [ keyWord + x for –x in matchWord]

# # def find(tree, char):

# #     if char == tree.data:
# #         print(tree.left.data + ' ' + tree.data + ' ' +tree.right.data)
# #         tree = tree.left
# #         print(tree.left.data + ' ' + tree.data + ' ' +tree.right.data)
# #         print(char + " found")
# #         return tree.left
# #         # print('selesai')
# #     elif tree.right != None:
# #         # print(char + ' asli dengan pohon '+ tree.data)
# #         tree = tree.right
# #         find(tree, char)
# #         # return tree.left
# #     else:
# #         return "Kata tidak ditemukan"

def tree2word(root, path, pathLen):

    if root is None: 
        return

    if(len(path) > pathLen):  
        path[pathLen] = root.data 
    else: 
        path.append(root.data) 

    pathLen = pathLen + 1

    if root.left is None and root.right is None: 
        return 
    else: 
        tree2word(root.left, path, pathLen) 
        tree2word(root.right, path, pathLen) 


        

kamus = Kamus('buka')
kamus.add('bubar')
kamus.add('asbak')
kamus.add('cair')
kamus.add('bro')
kamus.add('bros')
kamus.add('bulat')
kamus.add('bubuk')
kamus.add('bry')
kamus.print()

print(kamus.search('br'))
