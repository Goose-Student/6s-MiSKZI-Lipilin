import random

# Создаем список от 0 до 255
numbers = list(range(256))

# Рандомизируем список
random.shuffle(numbers)

# Выводим числа по 16 в строке
for i in range(0, len(numbers), 16):
    for j in range(i, min(i + 16, len(numbers))):
        print(f"0x{numbers[j]:02X}", end=", ")
    print()
