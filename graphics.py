from matplotlib import pyplot

def parse(path):
    x = []
    y = []
    file = open(path, "r")
    for line in file:
        line = line.replace("\n", "") 
        x.append(int(line.split(" ")[0]))
        y.append(int(line.split(" ")[1]))
    return x,y


# Значения до симуляции
x1, y1 = parse("input.txt")     
x3 = x1
y3 = [y1[i] * x1[i] for i in range(len(y1))]   

# Значения после симуляции
x2, y2 = parse("out.txt")       
x4 = x2
y4 = [y2[i] * x2[i] for i in range(len(y2))]


pyplot.subplot(2, 2, 1)
pyplot.bar(x1, y1)
pyplot.title('До симуляции')
pyplot.xlabel('Масса фракции')
pyplot.ylabel('Кол-во кластеров')

pyplot.subplot(2, 2, 2)
pyplot.bar(x2, y2)
pyplot.title('После симуляции')
pyplot.xlabel('Масса фракции')
pyplot.ylabel('Кол-во кластеров')

pyplot.subplot(2, 2, 3)
pyplot.bar(x3, y3)
pyplot.xlabel('Масса фракции')
pyplot.ylabel('Объём фракции')

pyplot.subplot(2, 2, 4)
pyplot.bar(x4, y4)
pyplot.xlabel('Масса фракции')
pyplot.ylabel('Объём фракции')

pyplot.gcf().canvas.set_window_title("Гистограммы")
pyplot.show()
