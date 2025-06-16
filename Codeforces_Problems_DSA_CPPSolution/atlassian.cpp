#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;


struct Receivable {
    std::string id;
    std::string card_type;
    std::string payout_date;
    int amount;
};

struct Contract {
    std::string contract_id;
    std::string merchant_id;
    std::string payout_date;
    std::string card_type;
    int amount;
};

std::vector<Receivable> update_receivables(const std::vector<Receivable>& registered_receivables, const std::vector<Contract>& contracts) {
    std::vector<Receivable> updated_receivables = registered_receivables;
    std::unordered_map<std::string, Receivable*> receivable_map;

    // Create a map for quick lookup of receivables
    for (auto& receivable : updated_receivables) {
        std::string key = receivable.id + "," + receivable.card_type + "," + receivable.payout_date;
        receivable_map[key] = &receivable;
    }

    // Process contracts and update receivables
    for (const auto& contract : contracts) {
        std::string key = contract.merchant_id + "," + contract.card_type + "," + contract.payout_date;
        auto it = receivable_map.find(key);
        if (it != receivable_map.end()) {
            // Update existing receivable
            it->second->amount -= contract.amount;
            if (it->second->amount < 0) {
                it->second->amount = 0;
            }
        } else {
            // Create new receivable for the contract
            updated_receivables.push_back({contract.merchant_id, contract.card_type, contract.payout_date, contract.amount});
        }
    }

    // Remove receivables with zero amount
    updated_receivables.erase(
        std::remove_if(updated_receivables.begin(), updated_receivables.end(),
                       [](const Receivable& r) { return r.amount == 0; }),
        updated_receivables.end());

    return updated_receivables;
}

int main() {
    // Sample input for registered receivables
    std::vector<Receivable> registered_receivables = {
        {"merchantA", "Visa", "2022-01-05", 500},
        {"merchantA", "Visa", "2022-01-05", 300},
        {"merchantB", "MasterCard", "2022-01-05", 1000}
    };

    // Sample input for contracts
    std::vector<Contract> contracts = {
        {"contract1", "merchantA", "2022-01-05", "Visa", 500}
    };

    // Update receivables
    std::vector<Receivable> updated_receivables = update_receivables(registered_receivables, contracts);

    // Print the updated receivables
    std::cout << "id,card_type,payout_date,amount\n";
    for (const auto& r : updated_receivables) {
        std::cout << r.id << "," << r.card_type << "," << r.payout_date << "," << r.amount << "\n";
    }

    return 0;
}