#include <iostream>
#include <stack>
#include <string>
using namespace std;

class TextEditor {
private:
    stack<string> undoStack;
    stack<string> redoStack;
    string currentText;
    string clipboard; // Clipboard to store copied text

public:
    // Type new text
    void type(const std::string& text) {
        undoStack.push(currentText);
        while (!redoStack.empty()) {
            redoStack.pop();
        }
        currentText += text;
    }

    // Copy selected text to clipboard
    void copy(size_t start, size_t length) {
        if (start < currentText.length()) {
            clipboard = currentText.substr(start, length);
        } else {
            std::cout << "Copy operation out of range.\n";
        }
    }

    // Paste clipboard content
    void paste() {
        if (!clipboard.empty()) {
            undoStack.push(currentText);
            while (!redoStack.empty()) {
                redoStack.pop();
            }
            currentText += clipboard;
        } else {
            std::cout << "Clipboard is empty.\n";
        }
    }

    // Undo last operation
    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(currentText);
            currentText = undoStack.top();
            undoStack.pop();
        } else {
            std::cout << "No actions to undo.\n";
        }
    }

    // Redo last undone operation
    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(currentText);
            currentText = redoStack.top();
            redoStack.pop();
        } else {
            std::cout << "No actions to redo.\n";
        }
    }

    // Display the current text
    void showText() const {
        std::cout << "Current Text: " << currentText << "\n";
    }
};

int main() {
    TextEditor editor;

    editor.type("Hello, ");
    editor.showText(); // Output: Hello, 

    editor.type("world!");
    editor.showText(); // Output: Hello, world!

    // Copy "world"
    editor.copy(7, 5);

    // Paste it
    editor.paste();
    editor.showText(); // Output: Hello, world!world

    editor.undo();
    editor.showText(); // Output: Hello, world!

    editor.redo();
    editor.showText(); // Output: Hello, world!world

    editor.undo();
    editor.showText(); 
    return 0;
}
