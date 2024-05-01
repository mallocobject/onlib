import random
import faker
# import os

fake = faker.Faker()

categories = ["Fiction", "Non-Fiction", "Science", "History", "Biography"]
authors = [fake.name() for _ in range(50)]  # Generate 50 author names

# path = os.getcwd() + '/asset/data.txt'
with open('./asset/data.txt', 'a') as f:
    for i in range(100):
        bookname = fake.catch_phrase()
        category = random.choice(categories)
        author = random.choice(authors)
        quantity = random.randint(1, 100)
        price = round(random.uniform(10, 100), 2)
        f.write(f"{bookname} | {category} | {author} | {quantity} | {price}\n")