
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Node {
public:
    int data;
    string address;
    bool dirty;
    Node* next;

    Node(const string& address, int data) {
        this->address = address;
        this->data = data;
        this->next = nullptr;
        this->dirty = false;
    }
};

class Cache {
    Node* head;
    string filename;

public:
    // Constructor to initialize cache and load data from file
    explicit Cache(const string &filename) {
        head = nullptr;
        this->filename = filename;
        initCache();
    }

    ~Cache() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Initializes the cache by reading data from a file
    void initCache() {
        ifstream file(filename);
        string line;


        getline(file, line);
        getline(file, line);
        getline(file, line);

        while (getline(file, line)) {
            string fileAddress;
            int data;
            convertLine(line, fileAddress, data);


            appendNode(intToHex(strToInt(fileAddress)), data);
        }

        file.close();
    }

    // Converts a string to an integer
    static int strToInt(const string &str) {
        int sum = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            sum = sum * 10 + (str[i] - '0');
        }


        return sum;
    }

    // Converts an integer to a string
    string intToStr(int num) {

        if (num == 0) {
            return "0";
        }

        string result = "";


        while (num > 0) {
            int digit = num % 10;
            char charDigit = '0' + digit;
            result += charDigit;
            num /= 10;
        }


        int n = strLength(result);
        for (int i = 0; i < n / 2; i++) {
            char temp = result[i];
            result[i] = result[n - i - 1];
            result[n - i - 1] = temp;
        }

        return result;
    }

    // Calculates the length of a string
    int strLength(const string &str) const {
        int length = 0;
        for (int i = 0; str[i] != '\0'; i++) {
            length++;
        }
        return length;
    }

    // Converts a hexadecimal string to an integer
    int hexToInt(const string& str) const {
        int sum = 0;
        int base = 1;

        for (int i = strLength(str) - 1; i >= 0; i--) {
            char digit = str[i];

            if (digit == ' ')
                continue;

            int value = 0;

            if (digit >= '0' && digit <= '9')
                value = digit - '0';
            else if (digit >= 'a' && digit <= 'f')
                value = digit - 'a' + 10;
            else
                cout << "Invalid hexadecimal digit " << digit << endl;

            sum += value * base;
            base *= 16;
        }

        return sum;
    }

    // Converts an integer to a hexadecimal string
    string intToHex(int value) const {
        if (value == 0)
            return "0";

        string hexadecimal = "";

        while (value > 0) {
            int remainder = value % 16;

            if (remainder < 10)
                hexadecimal = static_cast<char>(remainder + '0') + hexadecimal;
            else
                hexadecimal = static_cast<char>(remainder - 10 + 'a') + hexadecimal;

            value /= 16;
        }

        return hexadecimal;
    }

    // Converts a line from the file into address and data
    void convertLine(const string& line, string& address, int& data) const {
        string dataStr;
        bool extractingAddress = true;

        for (char ch : line) {
            if (ch == ',') {
                extractingAddress = false;
                continue;
            }

            if (extractingAddress) {
                address += ch;
            } else {
                dataStr += ch;
            }
        }


        data = hexToInt(dataStr);
    }

    // Reads data from cache file by address
    int readCache(const string& address) const {
        ifstream file(filename);
        string line;

        getline(file, line);
        getline(file, line);
        getline(file, line);

        while (getline(file, line)) {
            string fileAddress;
            int data;

            convertLine(line, fileAddress, data);

            if (fileAddress == address) {
                file.close();
                return data;
            }
        }

        file.close();
        return -1;
    }

    // Formats a hexadecimal string for display
    string formatHex(const string& hexStr) {
        int length = 0;


        while (hexStr[length] != '\0') {
            length++;
        }


        if (length == 4) {

            char formattedHex[6];
            formattedHex[0] = hexStr[0];
            formattedHex[1] = hexStr[1];
            formattedHex[2] = ' ';
            formattedHex[3] = hexStr[2];
            formattedHex[4] = hexStr[3];
            formattedHex[5] = '\0';

            return formattedHex;
        } else if (length == 3) {

            char formattedHex[5];
            formattedHex[0] = hexStr[0];
            formattedHex[1] = ' ';
            formattedHex[2] = hexStr[1];
            formattedHex[3] = hexStr[2];
            formattedHex[4] = '\0';

            return formattedHex;
        } else if (length == 2) {

            char formattedHex[3];
            formattedHex[0] = hexStr[0];
            formattedHex[1] = hexStr[1];
            formattedHex[2] = '\0';

            return formattedHex;
        } else if (length == 1) {

            char formattedHex[2];
            formattedHex[0] = hexStr[0];
            formattedHex[1] = '\0';

            return formattedHex;
        } else {

            return "";
        }
    }

    // Updates memory with new data for a specific address
    void updateMemory(const string& address, int data) {
        ifstream file(filename);
        ofstream tempFile("temp.csv");
        string line;

        getline(file, line);
        tempFile << line << endl;
        getline(file, line);
        tempFile << line << endl;
        getline(file, line);
        tempFile << line << endl;

        while (getline(file, line)) {
            string fileAddress;
            int fileData;
            convertLine(line, fileAddress, fileData);



            if (fileAddress == intToStr(hexToInt((address)))) {

                tempFile << address << "," << formatHex(intToHex(data)) << endl;

            } else {
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();
        remove(filename.c_str());
        rename("temp.csv", filename.c_str());
    }

    // Loads data into cache or updates cache if present
    void load(const string& address) {
        Node* node = getNode(intToHex(strToInt(address)));
        if (node != nullptr) {
            cout << "Cache Hit: Address " << address << " found in cache." << endl;
        } else {
            cout << "Cache Miss: Address " << address << " not found in cache. Loading..." << endl;
            int data = readCache(intToHex(strToInt(address)));
            appendNode(intToHex(strToInt(address)), data);
        }
    }

    // Stores data in cache or memory based on policies
    void store(const string& address, int data, bool writeThrough, bool writeAllocate) {
        Node* node = getNode(intToHex(strToInt(address)));

        if (node != nullptr) {
            cout << "Cache Hit: Address " << address << " found in cache. Updating... " << endl;
            if (writeThrough) {
                node->data = data;
                updateMemory(intToHex(strToInt(address)), data);
            } else {
                node->data = data;
                node->dirty = true;
            }
        } else {
            cout << "Cache Miss: Address " << address << " not found in cache. " << endl;
            if (writeAllocate) {
                cout << "Write Allocate: Loading data into cache and updating memory." << endl;
                appendNode(intToHex(strToInt(address)), data);
                updateMemory(intToHex(strToInt(address)), data);
            } else {
                cout << "Write Around: Writing directly to memory." << endl;
                updateMemory(intToHex(strToInt(address)), data);
            }
        }
    }

    // Returns the number of nodes in the cache
    int getLength() const {
        int length = 0;
        Node* temp = head;
        while (temp != nullptr) {
            temp = temp->next;
            length++;
        }

        return length;
    }


    // Evicts the oldest node from the cache
    void evictNode() {
        if (head == nullptr)
            return;

        Node* temp = head;
        head = head->next;
        delete temp;
    }

    // Appends a new node to the cache, evicting if necessary
    void appendNode(const string& address, int data) {
        if (getLength() == 20) {
            evictNode();
        }

        Node* newNode = new Node(address, data);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Finds a node in the cache by address
    Node* getNode(const string& address) const {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->address == address) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    // Displays the current state of the cache
    void displayCache() const {
        const Node* temp = head;
        while (temp != nullptr) {
            cout << "Address (Hex): " << temp->address << "\tData (Dec): " << temp->data << endl;
            temp = temp->next;
        }
    }
};

int main() {
    string filename = R"(D:\work\Assignment1DS\Memory.csv)";
    Cache cache(filename);

    cout << "Current cache: " << endl;
    cache.displayCache();


    string cacheHitPolicy, cacheMissPolicy;
    cout << "Select Cache Hit Policy (write-through / write-back): ";
    cin >> cacheHitPolicy;
    cout << "Select Cache Miss Policy (write-allocate / write-around): ";
    cin >> cacheMissPolicy;


    string address;
    int data;
    while (true) {
        cout << "Enter address in decimal (or type 'exit' to quit): ";
        cin >> address;
        if (address == "exit") break;

        cout << "Enter data in hexadecimal: ";
        cin >> hex >> data;


        bool writeThrough = (cacheHitPolicy == "write-through");
        bool writeAllocate = (cacheMissPolicy == "write-allocate");

        char operation;
        cout << "Enter operation type ('l' for load, 's' for store): ";
        cin >> operation;

        if (operation == 'l') {
            cache.load(address);
        } else if (operation == 's') {
            cache.store(address, data, writeThrough, writeAllocate);
        } else {
            cout << "Invalid operation." << endl;
        }

        cache.displayCache();
    }

    return 0;
}
