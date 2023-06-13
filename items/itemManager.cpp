#include "ItemManager.h"

// Constructor
ItemManager::ItemManager() : FileHandler("./dataBase/items.txt")
{
    Items.reserve(EXPECTED_LIST_SIZE); // Reserve space for efficient loading
    load();
}

// Destructor
ItemManager::~ItemManager()
{
    write(); // Save the items to file

    // Deallocate memory for each item
    /*
    for (auto i : Items)
        delete i;
    */
}

// Inline function to print a single item
inline void printSingleItem(User &user, int index, Item *i)
{
    std::cout << "| " << index << ". "; // Index is independent of vector index
    i->printInfo(user);
    if (i->getType() == DEVICE)
        std::cout << "|";
    std::cout << std::endl;
}

// Show the list of items
void ItemManager::showList(User &user, bool showActive)
{
    int idx = 1;
    for (auto i : Items)
    {
        if (!showActive && i->active())
            continue;
        printSingleItem(user, idx++, i);
    }
}

// Show the list of items filtered by type
void ItemManager::showList(User &user, Type typeFilter, bool showActive)
{
    // int idx = 1;
    for (auto i : Items)
    {
        if ((!showActive && i->active()) || i->getType() != typeFilter) // Skip if not matching type
            continue;
        printSingleItem(user, i->getId(), i);
    }
}

// Add an item to the list
void ItemManager::addItem(Item *item)
{
    Items.push_back(item);
}

// Delete an item from the list by ID
void ItemManager::deleteItem(int id)
{
    std::vector<Item *>::iterator target;
    for (std::vector<Item *>::iterator it = Items.begin(); it < Items.end(); it++)
    {
        if ((*it)->getId() == id)
        {
            target = it;
            break;
        }
    }
    std::iter_swap(target, Items.end() - 1);
    Items.pop_back();
}

// Get an item from the list by ID
Item *ItemManager::getItem(int id)
{
    for (auto i : Items)
    {
        if (i->getId() == id)
            return i;
    }
    std::cerr << "no item found." << std::endl;
    return 0;
}

// Get an item from the list by name
Item *ItemManager::getItem(std::string name)
{
    for (auto i : Items)
    {
        if (i->getName() == name)
            return i;
    }
    std::cerr << "no item found." << std::endl;
    return 0;
}

// Get the latest ID in the list
int ItemManager::getLatestId()
{
    int maxId = 0;
    for (auto i : Items)
    {
        if (i->getId() > maxId)
            maxId = i->getId();
    }
    return maxId + 1;
}

// Load items from file
void ItemManager::load()
{
    file.open(saveLocation, std::ios::in); // Open file in read mode
    std::vector<std::string> buffer;       // Buffer to hold file contents
    char temp[MAX_BUFFER_SIZE];            // Temporary string for buffering
    while (file.getline(temp, MAX_BUFFER_SIZE))
    {
        buffer.push_back((std::string)temp); // Store each line of the file in the buffer
        file.clear();                        // Reset the flags after reading each line
    }
    for (auto text : buffer)
    {
        std::stringstream ss(text);       // Create a stringstream to parse the text
        std::string type, name, isActive; // Common item members
        int id;
        ss >> type;            // The structure of the parsed sentence depends on the type
        if (type == "ACCOUNT") // ACCOUNT accountType name id isActive (uuid startTime)
        {
            std::string accountType;
            int uuid;
            time_t startTime;
            ss >> accountType >> name >> id >> isActive; // Read up to 'isActive'
            if (id == -1)
                id = getLatestId(); // Generate a new ID if it's not valid
            if (isActive == "ACTIVE")
            {
                ss >> uuid >> startTime; // Read 'uuid' and 'startTime'
                Account *a = new Account(accountType, name, id, true, uuid, startTime);
                addItem(a);
            }
            else if (isActive == "INACTIVE")
            {
                Account *a = new Account(accountType, name, id, false);
                addItem(a);
            }
            else // Parsing failed if the isActive value is invalid
            {
                std::cerr << "parsing failed.";
            }
        }
        else if (type == "DEVICE") // DEVICE name id isActive
        {
            ss >> name >> id >> isActive;
            if (id == -1)
                id = getLatestId(); // Generate a new ID if it's not valid
            bool isActiveBool;
            if (isActive == "ACTIVE")
                isActiveBool = true;
            else if (isActive == "INACTIVE")
                isActiveBool = false;
            else // Parsing failed if the isActive value is invalid
                std::cerr << "parsing failed.";
            addItem(new Device(name, id, isActiveBool));
        }
    }
    file.close(); // File will not be read again
}

// Write items to file
void ItemManager::write()
{
    file.clear();
    file.open(saveLocation, std::ios::out | std::ios::trunc); // Completely overwrite the file
    for (auto i : Items)
    {
        if (i->getType() == ACCOUNT)
        {
            Account *ii = dynamic_cast<Account *>(i); // Downcast is necessary
            file << "ACCOUNT " << ii->getAccountType() << " " << ii->getName() << " " << ii->getId();
            if (ii->active())
            {
                file << " ACTIVE " << ii->getcontrollerId() << " " << ii->getStartTime() << std::endl;
            }
            else
            {
                file << " INACTIVE" << std::endl;
            }
        }
        else if (i->getType() == DEVICE)
        {
            Device *ii = dynamic_cast<Device *>(i); // Downcast is not necessary but kept for consistency
            file << "DEVICE " << ii->getName() << " " << ii->getId();
            if (ii->active())
            {
                file << " ACTIVE" << std::endl;
            }
            else
            {
                file << " INACTIVE" << std::endl;
            }
        }
    }
    file.close();
}
