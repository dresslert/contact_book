# **Contact Management System**

This is a simple contact management system implemented in C. The program allows users to:

- **Add a Contact**: Enter name, telephone number, and email to add a new contact.
- **Search for a Contact**: Find contacts by name, with support for partial matches.
- **Display a Contact**: View details of a specific contact by its index.
- **Edit a Contact**: Update details of an existing contact, with options to leave fields unchanged.
- **Remove a Contact**: Delete a contact by name.
- **List All Contacts**: Display a list of all contacts.
- **Save Contacts**: Save all contacts to a file (`contacts.txt`).
- **Load Contacts**: Load contacts from the file (`contacts.txt`) upon startup.
- **Sort Contacts**: Automatically sorts contacts by name for better organization.

## **Features**
- Data is stored persistently in a text file.
- Contacts are sorted alphabetically by name.
- Partial name search functionality for improved flexibility.

## **Usage**

Compile the code using a C compiler:

```bash
gcc -o agenda_gtk agenda_gtk.c
