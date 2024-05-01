import random
import faker

fake = faker.Faker()

categories = ["Fiction", "Non-Fiction", "Science", "History", "Biography"]
authors = [''.join(fake.name().split()) for _ in range(50)]  # Generate 50 author names without spaces

with open('./asset/data.txt', 'a') as f:
    for i in range(100):
        bookname = ''.join(fake.catch_phrase().split())
        category = random.choice(categories)
        author = random.choice(authors)
        quantity = random.randint(1, 100)
        price = round(random.uniform(10, 100), 2)
        f.write(f"{bookname}|{category}|{author}|{quantity}|{price}\n")