// Muhammad Abdullah ALi
// i23-2523
// Data Structures Assignment Number 1

#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;

// Opens an HTML file based on the operating system
void openHtmlFile(const std::string& filePath) {
#ifdef _WIN32
    std::string command = "start " + filePath;
#elif __linux__
    std::string command = "xdg-open " + filePath;
#elif __APPLE__
    std::string command = "open " + filePath;
#else
    std::cerr << "Unsupported operating system" << std::endl;
    return;
#endif
    std::system(command.c_str());
}

class Node {
public:
    string url;
    int frequency;
    Node* next;

    explicit Node(const string& u) {
        url = u;
        frequency = 1;
        next = nullptr;
    }
};

class BrowserHistory {
private:
    Node* head;
    Node* current;

public:
    BrowserHistory() {
        head = nullptr;
        current = nullptr;
    }

    ~BrowserHistory() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
    }

    // Creates an HTML file with the given URL as content
    void createHtmlFile(const string& url) const {
        ofstream file(url + ".html");
        if (file.is_open()) {
            file << "<!DOCTYPE html>\n";
            file << "<html lang=\"en\">\n";
            file << "<head>\n";
            file << "    <meta charset=\"UTF-8\">\n";
            file << "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
            file << "    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n";
            file << "    <title>" << url << "</title>\n";
            file << "    <style>\n";
            file << "        body { font-family: Arial, sans-serif; margin: 20px; }\n";
            file << "        h1 { color: #333; }\n";
            file << "    </style>\n";
            file << "</head>\n";
            file << "<body>\n";
            file << "    <h1>Welcome to " << url << "</h1>\n";
            file << "    <p>This is the HTML file generated for the site: " << url << ".</p>\n";
            file << "</body>\n";
            file << "</html>\n";
            file.close();
        }
    }

    // Clears forward browsing history from the current node
    void clearForwardHistory(Node* current) const {
        Node* temp = current->next;
        while (temp != nullptr) {
            Node* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }

        current->next = nullptr;
        cout << "Forward history cleared.\n";
    }

    // Returns the number of nodes in the browsing history
    int getSize() const {
        int size = 0;
        Node* temp = head;
        while (temp != nullptr) {
            temp = temp->next;
            size++;
        }

        return size;
    }

    // Finds a node with the specified URL in the browsing history
    Node* findUrl(const string& url) const {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->url == url) {
                return temp;
            }

            temp = temp->next;
        }

        return nullptr;
    }

    // Validates if the given URL contains invalid characters
    bool isValidURL(const string& url) const {

        char invalidChars[] = {' ', '<', '>', '#', '%', '{', '}', '|', '\\', '^', '~', '[', ']', '`'};
        int invalidCharCount = sizeof(invalidChars) / sizeof(invalidChars[0]);


        for (int i = 0; i < url.length(); i++) {
            char c = url[i];

            for (int j = 0; j < invalidCharCount; j++) {
                if (c == invalidChars[j]) {
                    return false;
                }
            }
        }

        return true;
    }

    // Visits a URL, updates history, and creates an HTML file
    void visit(const string& url) {
        if (url.empty()) {
            cout << "Empty URL is not valid. Please enter a valid URL.\n";
            return;
        }

        if (!isValidURL(url)) {
            cout << "Invalid URL. Please enter a valid URL without spaces or special characters.\n";
            return;
        }

        Node* foundNode = findUrl(url);

        if (foundNode != nullptr) {
            foundNode->frequency++;
            current = foundNode;
        } else {
            if (current != nullptr && current->next != nullptr) {
                clearForwardHistory(current);
            }

            Node* newNode = new Node(url);
            if (current == nullptr) {
                head = newNode;
            } else {
                current->next = newNode;
            }
            current = newNode;
        }

        createHtmlFile(url);
        openHtmlFile(url + ".html");
    }

    // Moves forward in the browsing history by a specified number of steps
    string forward(const int steps) {
        if (current == nullptr) return "No history";

        clearForwardHistory(current);

        for (int i = 0; i < steps && current->next != nullptr; i++) {
            current = current->next;
        }

        openHtmlFile(current->url + ".html");
        return current->url;
    }

    // Moves back in the browsing history by a specified number of steps
    string back(int steps) {
        if (current == nullptr || current == head) {
            return "No previous URL";
        }

        while (steps > 0 && current != head) {
            Node* temp = head;


            while (temp->next != current) {
                temp = temp->next;
            }

            current = temp;
            steps--;
        }

        openHtmlFile(current->url + ".html");
        clearForwardHistory(current);
        return current->url;
    }

    // Displays the entire browsing history with URL frequencies
    void displayHistory() const {
        if (head == nullptr) {
            cout << "No browsing history available." << endl;
            return;
        }

        Node* temp = head;
        int count = 1;

        cout << "\nBrowsing History" << endl;
        while (temp != nullptr) {
            cout << count << ". URL: " << temp->url << " | Frequency: " << temp->frequency << endl;
            temp = temp->next;
            count++;
        }
        cout << endl;
    }

    // Displays the top K most frequently visited URLs
    void topKFrequent(const int k) const {
        int size = getSize();
        if (size == 0) {
            cout << "No history available." << endl;
            return;
        }

        Node** arr = new Node*[size];
        Node* temp = head;
        int count = 0;
        while (temp != nullptr) {
            arr[count++] = temp;
            temp = temp->next;
        }


        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (arr[j]->frequency < arr[j + 1]->frequency) {
                    Node* tempNode = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = tempNode;
                }
            }
        }

        for (int i = 0; i < k && i < count; i++) {
            cout << "URL: " << arr[i]->url << " | Frequency: " << arr[i]->frequency << endl;
            openHtmlFile(arr[i]->url + ".html");
        }

        delete[] arr;
    }
};

int main() {
    BrowserHistory browserHistory;
    int choice, steps, k;
    string url;

    while (true) {
        cout << "\nBrowser History Simulation" << endl;
        cout << "1. Visit a URL" << endl;
        cout << "2. Move back in history" << endl;
        cout << "3. Move forward in history" << endl;
        cout << "4. Display top K most frequently visited URLs" << endl;
        cout << "5. Display all history" << endl;
        cout << "6. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Enter the URL to visit: ";
                getline(cin, url);
                browserHistory.visit(url);
                break;
            case 2:
                cout << "Enter the number of steps to move back: ";
                cin >> steps;
                cout << "Moved back to: " << browserHistory.back(steps) << endl;
                break;
            case 3:
                cout << "Enter the number of steps to move forward: ";
                cin >> steps;
                cout << "Moved forward to: " << browserHistory.forward(steps) << endl;
                break;
            case 4:
                cout << "Enter the value of K: ";
                cin >> k;
                browserHistory.topKFrequent(k);
                break;
            case 5:
                browserHistory.displayHistory();
                break;
            case 6:
                cout << "Exiting browser history simulation." << endl;
                return 0;
            default:
                cout << "Invalid option! Please choose a valid option." << endl;
        }
    }
}
