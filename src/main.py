import argparse
import json
import os

MESSAGES_FILE = "messages.json"

def load_messages():
    if os.path.exists(MESSAGES_FILE):
        with open(MESSAGES_FILE, 'r') as f:
            return json.load(f)
    return []

def save_messages(messages):
    with open(MESSAGES_FILE, 'w') as f:
        json.dump(messages, f, indent=2)

def add_message(message):
    messages = load_messages()
    messages.append(message)
    save_messages(messages)

def list_messages():
    messages = load_messages()
    if not messages:
        print("No messages found.")
    else:
        for i, msg in enumerate(messages, 1):
            print(f"{i}. {msg}")

def main():
    parser = argparse.ArgumentParser(description="Manage text messages")
    parser.add_argument("-m", "--message", type=str, help="Add a new message")
    parser.add_argument("-l", "--list", action="store_true", help="List all messages")

    args = parser.parse_args()

    if args.message:
        add_message(args.message)
        print(f"Message '{args.message}' added.")

    if args.list:
        list_messages()

if __name__ == "__main__":
    main()