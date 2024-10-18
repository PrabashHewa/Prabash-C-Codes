/**
 * The Familytree class provides functionalities to manage family relationships,
 * including adding members, defining relationships, and retrieving information
 * about individuals and their lineage. The key methods include:
 *
 * printCousins: Outputs the cousins of a specified person.
 * printSiblings: Outputs the siblings of a specified person.
 * printParents: Outputs the parents of a specified person.
 * printTallestInLineage: Finds and prints the tallest ancestor of a specified person.
 * printShortestInLineage: Finds and prints the shortest ancestor of a specified person.
 * printGrandChildrenN: Counts and outputs the number of grandchildren for a specified person.
 * printGrandParentsN: Counts and outputs the number of grandparents for a specified person.
 *
 * Each method is designed to navigate through the family tree, utilizing the
 * relationships defined in the Person class, which includes attributes for parents,
 * children, and height.
 *
 * Name : Prabash Madusanka
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <stack>
#include "familytree.hh"

/**
 * @brief Default constructor for the Familytree class.
 *
 * @return Initializes the family tree without any persons.
 */
Familytree::Familytree() = default;

/**
 * @brief Find a person by ID.
 *
 * @param id The ID of the person to find.
 * @return Pointer to the Person object if found, nullptr otherwise.
 */
Person* Familytree::getPointer(const std::string& id) const {
    auto it = persons_.find(id);

    if (it != persons_.end()) {
        return it->second;
    }

    return nullptr;
}

/**
 * @brief Prints an error message when a person is not found.
 *
 * @param id The ID of the person not found.
 * @param output The output stream to write the error message.
 */
void Familytree::printNotFound(const std::string& id, std::ostream& output) const {
    output << "Error. " << id << " not found." << std::endl;
}

/**
 * @brief Convert a vector of persons to a set of IDs.
 *
 * @param container A vector of pointers to Person objects.
 * @return A set of IDs corresponding to the persons in the vector.
 */
IdSet Familytree::vectorToIdSet(const std::vector<Person*>& container) const {
    IdSet id_set;
    for (const auto& person : container) {
        if (person != nullptr) {
            id_set.insert(person->id_);
        }
    }
    return id_set;
}

/**
 * @brief Prints a group of related persons .
 *
 * @param id The ID of the person whose group is being printed.
 * @param group The type of group .
 * @param container The set of IDs to print.
 * @param output The output stream to write the group information.
 */
void Familytree::printGroup(const std::string& id, const std::string& group, const IdSet& container, std::ostream& output) const {
    int count = container.size();
    if (count == 0) {
        output << id << " has no " << group << "." << std::endl;
    } else {
        output << id << " has " << count << " " << group << (count == 1 ? ":" : ":") << std::endl;
        for (const auto& memberId : container) {
            output << memberId << std::endl;
        }
    }
}

/**
 * @brief Checks if a person exists in the family tree.
 *
 * @param id The ID of the person to check.
 * @return True if the person exists, false otherwise.
 */
bool Familytree::personExists(const std::string& id) const {
    return getPointer(id) != nullptr;
}

/**
 * @brief Load family tree data from a file.
 *
 * @param filename The name of the file to load data from.
 * @param output The output stream for error messages or confirmations.
 */
void Familytree::loadFromFile(const std::string& filename, std::ostream& output) {
    std::ifstream input(filename);
    if (!input) {
        output << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::vector<std::pair<std::string, std::vector<std::string>>> to_add; // To store person IDs and their parents

    // Load all persons
    while (std::getline(input, line)) {
        std::vector<std::string> parts;
        std::stringstream ss(line);
        std::string item;

        while (std::getline(ss, item, ';')) {
            parts.push_back(item);
        }

        if (parts.size() < 2) {
            output << "Invalid line format: " << line << std::endl;
            continue;
        }

        std::string id = parts[0];
        int height = std::stoi(parts[1]);

        addNewPerson(id, height, output);

        // Store the parents for this person for later processing
        std::vector<std::string> parents;
        for (size_t i = 2; i < parts.size(); ++i) {
            if (!parts[i].empty()) {
                parents.push_back(parts[i]);
            }
        }

        to_add.emplace_back(id, parents);
    }

    // Establish relationships
    for (const auto& entry : to_add) {
        const auto& id = entry.first;
        const auto& parents = entry.second;
        addRelation(id, parents, output);
    }

    input.close();
}

/**
 * @brief Add a new person to the family tree.
 *
 * @param id The ID of the person to add.
 * @param height The height of the person.
 * @param output The output stream for error messages.
 */
void Familytree::addNewPerson(const std::string& id, int height, std::ostream& output) {
    if (id.empty()) {
        output << "Error. Invalid ID: " << id << std::endl;
        return;
    }

    // Check person is already added
    auto it = persons_.find(id);
    if (it != persons_.end()) {
        output << "Error. Person already added." << std::endl;
        return;
    }

    // Create a new person
    Person* newPerson = new Person{id, height};

    persons_[id] = newPerson;
    //output << id << ", " << height << std::endl; // Print added message
}

/**
 * @brief Adds a parent-child relationship between a child and their parents.
 *
 * @param child The ID of the child.
 * @param parents A vector of parent IDs.
 * @param output The output stream for error messages.
 */
void Familytree::addRelation(const std::string& child,
                             const std::vector<std::string>& parents,
                             std::ostream& output) {
    // Find the child in the persons_ map
    Person* childPtr = getPointer(child);

    if (childPtr == nullptr) {
        printNotFound(child, output);
        return;
    }

    // Loop over the parents list to add parent-child relationship
    for (size_t i = 0; i < parents.size(); ++i) {
        const std::string& parentId = parents[i];

        if (parentId == "-") {
            continue;
        }

        Person* parentPtr = getPointer(parentId);

        if (parentPtr == nullptr) {
            printNotFound(parentId, output);
            continue;
        }

        // Link the child with the parent
        childPtr->parents.push_back(parentPtr);
        parentPtr->children_.push_back(childPtr);
    }
}

/**
 * @brief Prints all persons in the family tree, sorted by ID.
 *
 * @param output The output stream to write the person information.
 */
void Familytree::printPersons(Params, std::ostream &output) const {
    std::vector<const Person*> sorted_persons;
    for (const auto& pair : persons_) {
        sorted_persons.push_back(pair.second);
    }
    std::sort(sorted_persons.begin(), sorted_persons.end(), [](const Person* a, const Person* b) {
        return a->id_ < b->id_;  // Sort alphabetically by name (id)
    });

    for (const auto* person : sorted_persons) {
        output << person->id_ << ", " << person->height_ << std::endl;
    }
}

/**
 * @brief Prints the children of a person.
 *
 * @param params Parameters containing the person's ID.
 * @param output The output stream to write the children information.
 */
void Familytree::printChildren(Params params, std::ostream& output) const {
    if (params.empty()) {
        output << "Error: No ID provided." << std::endl;
        return;
    }

    Person* person = getPointer(params[0]);
    if (!person) {
        printNotFound(params[0], output);
        return;
    }

    IdSet children_ids = vectorToIdSet(person->children_);
    printGroup(person->id_, "children", children_ids, output);
}

/**
 * @brief Prints the parents of a person.
 *
 * @param params Parameters containing the person's ID.
 * @param output The output stream to write the parents information.
 */
void Familytree::printParents(Params params, std::ostream& output) const {
    if (params.empty()) {
        output << "Error: No ID provided." << std::endl;
        return;
    }

    Person* person = getPointer(params[0]);
    if (person == nullptr) {
        // Print error message if the person is not found
        printNotFound(params[0], output);
        return;
    }
    printGroup(person->id_, "parents", vectorToIdSet(person->parents), output);
}

/**
 * @brief Prints the siblings of a person.
 *
 * @param params Parameters containing the person's ID.
 * @param output The output stream to write the siblings information.
 */
void Familytree::printSiblings(Params params, std::ostream& output) const {
    if (params.empty()) {
        output << "Error: No ID provided." << std::endl;
        return;
    }

    Person* person = getPointer(params[0]);
    if (person == nullptr) {
        // Print error message if the person is not found
        printNotFound(params[0], output);
        return;
    }

    IdSet siblings_set;
    for (const auto& parent : person->parents) {
        for (const auto& sibling : parent->children_) {
            if (sibling != person) {
                siblings_set.insert(sibling->id_);
            }
        }
    }
    printGroup(person->id_, "siblings", siblings_set, output);
}

/**
 * @brief Prints the cousins of a person.
 *
 * @param params Parameters containing the person's ID.
 * @param output The output stream to write the cousins' information.
 */
void Familytree::printCousins(Params params, std::ostream& output) const {
    if (params.empty()) {
        output << "Error: No ID provided." << std::endl;
        return;
    }

    Person* person = getPointer(params[0]);
    if (person == nullptr) {
        printNotFound(params[0], output);
        return;
    }

    IdSet cousins_set;
    std::set<Person*> aunts_uncles;

    // Logic to gather cousins
    for (const auto& parent : person->parents) {
        for (const auto& grandparent : parent->parents) {
            for (const auto& aunt_uncle : grandparent->children_) {
                if (aunt_uncle != parent) {
                    aunts_uncles.insert(aunt_uncle);
                }
            }
        }
    }

    for (const auto& aunt_uncle : aunts_uncles) {
        for (const auto& cousin : aunt_uncle->children_) {
            cousins_set.insert(cousin->id_);
        }
    }

    printGroup(person->id_, "cousins", cousins_set, output);
}

/**
 * @brief Prints the tallest person in the lineage of a given person.
 *
 * @param params Parameters containing the person's ID.
 * @param output The output stream to write the tallest person's information.
 */
void Familytree::printTallestInLineage(Params params, std::ostream& output) const {
    if (params.size() != 1) {
        printNotFound(params[0], output);
        return;
    }

    std::string id = params[0];

    // Check if the person exists
    Person* person = getPointer(id);
    if (!person) {
        printNotFound(id, output);
        return;
    }

    Person* tallestPerson = person;
    int tallestHeight = person->height_;

    std::set<Person*> visited;

    // Helper function to find the tallest descendant
    std::function<void(Person*)> findTallest = [&](Person* current) {
        visited.insert(current);

        // Check each child of the current person
        for (Person* child : current->children_) {
            if (visited.find(child) == visited.end()) {
                if (child->height_ > tallestHeight) {
                    tallestHeight = child->height_;
                    tallestPerson = child;
                }
                findTallest(child);
            }
        }
    };

    findTallest(person);

    // Prepare output based on whether the tallest is the person or a descendant
    if (tallestPerson == person) {
        output << "With the height of " << tallestHeight << ", " << id
               << " is the tallest person in his/her lineage." << std::endl;
    } else {
        output << "With the height of " << tallestHeight << ", "
               << tallestPerson->id_ << " is the tallest person in "
               << id << "'s lineage." << std::endl;
    }
}

/**
 * @brief Prints the shortest person in the lineage of a given person.
 *
 * @param params Parameters containing the person's ID.
 * @param output The output stream to write the shortest person's information.
 */
void Familytree::printShortestInLineage(Params params, std::ostream& output) const {
    if (params.size() != 1) {
        printNotFound(params[0], output);
        return;
    }

    std::string id = params[0];

    // Check if the person exists
    Person* person = getPointer(id);
    if (!person) {
        printNotFound(id, output);
        return;
    }

    Person* shortestPerson = person;
    int shortestHeight = person->height_;

    std::set<Person*> visited;

    // Helper function to find the shortest descendant
    std::function<void(Person*)> findShortest = [&](Person* current) {
        visited.insert(current);

        // Check each child of the current person
        for (Person* child : current->children_) {
            if (visited.find(child) == visited.end()) {
                if (child->height_ < shortestHeight) {
                    shortestHeight = child->height_;
                    shortestPerson = child;
                }
                findShortest(child);
            }
        }
    };

    findShortest(person);

    // Prepare output based on whether the shortest is the person or a descendant
    if (shortestPerson == person) {
        output << "With the height of " << shortestHeight << ", " << id
               << " is the shortest person in his/her lineage." << std::endl;
    } else {
        output << "With the height of " << shortestHeight << ", "
               << shortestPerson->id_ << " is the shortest person in "
               << id << "'s lineage." << std::endl;
    }
}

/**
 * @brief Prints the number of grandchildren for a given person.
 *
 * @param params Parameters containing the person's ID.
 * @param output The output stream to write the grandchildren's information.
 */
void Familytree::printGrandChildrenN(Params params, std::ostream& output) const {
    if (params.size() != 2) {
        output << "Error. Invalid number of parameters." << std::endl;
        return;
    }

    std::string id = params[0];
    int level = std::stoi(params[1]);

    if (level < 1) {
        output << WRONG_LEVEL << std::endl;
        return;
    }

    Person* person = getPointer(id);
    if (!person) {
        printNotFound(id, output);
        return;
    }

    std::set<std::string> grandchildren_ids;
    std::function<void(Person*, int)> findGrandChildren = [&](Person* current, int currentLevel) {
        if (currentLevel > level) return;

        // Increment level to find the next generation
        if (currentLevel == level) {
            for (const auto& child : current->children_) {
                for (const auto& grandchild : child->children_) {
                    grandchildren_ids.insert(grandchild->id_);
                }
            }
        }

        // Recursively search for grandchildren
        for (const auto& child : current->children_) {
            findGrandChildren(child, currentLevel + 1);
        }
    };

    findGrandChildren(person, 1);

    size_t count = grandchildren_ids.size();

    // Generate the correct grandchildren label based on the level
    std::string childLabel;
    if (level == 1) {
        childLabel = "grandchildren";
    } else {
        childLabel = "great-";
        for (int i = 2; i < level; ++i) {
            childLabel += "great-";
        }
        childLabel += "grandchildren";
    }

    if (count == 0) {
        output << id << " has no " << childLabel << "." << std::endl;
    } else {
        output << id << " has " << count << " " << childLabel << ":" << std::endl;
        for (const auto& grandchild_id : grandchildren_ids) {
            output << grandchild_id << std::endl;
        }
    }
}

/**
 * @brief Prints the number of grandparents for a given person.
 *
 * @param params Parameters containing the person's ID.
 * @param output The output stream to write the grandparents' information.
 */
void Familytree::printGrandParentsN(Params params, std::ostream& output) const {
    if (params.size() != 2) {
        output << "Error. Invalid number of parameters." << std::endl;
        return;
    }

    std::string id = params[0];
    int level = std::stoi(params[1]);

    if (level < 1) {
        output << WRONG_LEVEL << std::endl;
        return;
    }

    Person* person = getPointer(id);
    if (!person) {
        printNotFound(id, output);
        return;
    }

    std::set<std::string> ancestors;

    // Helper function to find ancestors
    std::function<void(Person*, int)> findAncestorsAtLevel = [&](Person* current, int currentLevel) {
        if (currentLevel > level) return;

                if (currentLevel == level) {
                    for (const auto& gparent : current->parents) {
                        for (const auto& grandparent : gparent->parents) {
                            ancestors.insert(grandparent->id_);
                }
            }
        } else {
            for (const auto& gparent : current->parents) {
                findAncestorsAtLevel(gparent, currentLevel + 1);

            }
        }
    };

    findAncestorsAtLevel(person, 1);

    size_t count = ancestors.size();

    // Generate the correct ancestor label based on the level
    std::string ancestorLabel;
    if (level == 1) {
        ancestorLabel = "grandparents";
    } else {
        ancestorLabel = "great-";
        for (int i = 2; i < level; ++i) {
            ancestorLabel += "great-";
        }
        ancestorLabel += "grandparents";
    }

    if (count == 0) {
        output << id << " has no " << ancestorLabel << "." << std::endl;
    } else {
        output << id << " has " << count << " " << ancestorLabel << ":" << std::endl;
        for (const auto& ancestor_id : ancestors) {
            output << ancestor_id << std::endl;
        }
    }
}








