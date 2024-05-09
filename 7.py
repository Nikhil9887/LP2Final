import random

# Function to convert input to lowercase


def to_lowercase(s):
    return s.lower()


def greet():
    """Greets the customer with a random welcome message."""
    greetings = ["Hello! Welcome to Myntra customer service. How can I assist you today?",
                 "Hi there! Are you looking for information about a product or need help with your order?"]
    return greetings[random.randint(0, len(greetings)-1)]


def answer(question):
    """Provides a response to the customer's question based on keywords and placeholders."""
    responses = {
        "delivery times": "Delivery times typically range from {min_days} to {max_days} business days depending on your location and chosen shipping option. You can find more details on the product page.",
        "return an item": "For hassle-free returns, you can visit our Returns Center at our official website",
        "track my order": "Absolutely! You can track your order by signing in to your myntra account and going to 'Your Orders'.",
        "specific product": "Sure, tell me more about the product you're interested in.  What's the name or do you have a link?",
        "speak to a representative": "I understand. While I can answer most questions, you can connect with a live representative through our online chat option on the Myntra website.",
        "order status": "To check your order status, can I get your order number?",
        "return the item": "For return requests, please visit our Returns & Exchanges page on the Myntra website.",
        "size chart": "You can refer to our size guide available on the product page to find the perfect fit.",
        "discount going on": "hello there!! you will find details of discount and sales on homepage or while purchasing the product.",
        "complaint regarding item": "I'm sorry to hear that. Please share your concern, and I'll do my best to assist you.",
    }
    best_match = None
    best_match_score = 0
    for key, value in responses.items():
        score = sum(word in to_lowercase(question)
                    for word in to_lowercase(key).split())
        if score > best_match_score:
            best_match = key
            best_match_score = score

    # Personalize response using placeholders and ask follow-up questions
    if best_match:
        response = responses[best_match]
        if "min_days" in response:
            # Replace with actual delivery timeframes
            response = response.format(min_days=3, max_days=7)
        if best_match == "order status":
            # Ask for order number and offer further assistance with limitations disclaimer
            order_number = input(
                "Myntra Rep: Please enter your order number: ")
            response += f"\n I cannot access specific order details yet, but your order number is {order_number}. For detailed order information, please visit your Myntra account. Would you like help with anything else?"
    else:
        response = "I apologize, I couldn't quite understand that. Can you rephrase or ask something different? Perhaps you're looking for information about our popular categories like electronics or clothing?"
    return response


def main():
    """Runs the main loop of the chatbot interaction."""
    print(greet())

    while True:
        user_input = input("Customer: ")
        if user_input.lower() == "bye":
            print("Myntra Rep: Thank you for contacting Myntra! Have a great day.")
            break
        print("Myntra Rep:", answer(user_input))


if __name__ == "main":
    main()
