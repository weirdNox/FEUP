def readIntegerFromFile(filename):
  myfile = open(filename)
  for line in myfile:
    result= int(line)
  myfile.close()
  return result

def readFloatFromFile(filename):
  myfile = open(filename)
  for line in myfile:
    result= float(line)
  myfile.close()
  return result

def readArrayFromFile(filename):
  result = []
  myfile = open(filename)
  for line in myfile:
    result.append(float(line))
  myfile.close()
  return result

def readMatrixFromFile(filename):
  result = [[]]
  myfile = open(filename)
  for line in myfile:
    result.append(sepCommas(line))
  myfile.close()
  del result[0]
  return result

def sepCommas(mystr):
  elem=[]
  auxstr=''
  for i in range(0,len(mystr)):
    if mystr[i]==',':
      elem.append(float(auxstr))
      auxstr=''
    else:
      if mystr[i]!='\n':
        auxstr=auxstr+mystr[i]
  elem.append(float(auxstr))
  return elem
