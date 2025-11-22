//
// Created by Jar Jar Banton on 17. 11. 2025.
//

#ifndef SKUPINOVA_PRACE_2025_INVENTORY_H
#define SKUPINOVA_PRACE_2025_INVENTORY_H


#include <string>
#include <vector>
#include <optional>

// forward-declare global Item from loot system (defined in loot.h)
struct Item;

class inventory {
public:
	enum class ItemType { Weapon, Potion, Armor, Misc };

	struct Item {
		std::string name;
		ItemType type;
		int quantity{1};
		//pridan combat bonus pro vypocet v statbaru
		int combatBonus = 0;

		Item() = default;
		Item(std::string n, ItemType t, int q = 1) : name(std::move(n)), type(t), quantity(q) {}
	};

	// Constructor sets slot limits (defaults reasonable for the game)
	// added maxArmors to control how many different armors can be carried
	inventory(int maxWeapons = 2, int maxPotions = 5, int maxArmors = 2, int equipSlots = 2);

	// Inventory operations
	bool addItem(const Item& item); // returns false if no space
	bool removeItem(const std::string& name, int qty = 1);

	// Equip/unequip
	// equip slot indices are 0..equipSlots-1
	bool equipItem(const std::string& name, int slot = 0);
	bool unequip(int slot);

	// Gold management
	void addGold(int amount);
	bool spendGold(int amount);
	int getGold() const;

	// Text UI: prints the inventory to stdout
	void display() const;

	// Add loot dropped in the world (from global loot system)
	// Returns true if the loot was added (or gold collected). If false,
	// the item could not be added due to inventory limits.
	bool addLoot(const ::Item& loot);
	// Add multiple loot items (returns true if all were added)
	bool addLoot(const std::vector<::Item>& loot);

	// Accessors
	int maxWeapons() const { return maxWeapons_; }
	int maxPotions() const { return maxPotions_; }
	int maxArmors() const { return maxArmors_; }
	int equipSlots() const { return equipSlots_; }

private:
	int maxWeapons_;
	int maxArmors_;
	int maxPotions_;
	int equipSlots_;

	std::vector<Item> weapons_;
	std::vector<Item> armors_;
	std::vector<Item> potions_;
	std::vector<Item> misc_;
	std::vector<std::optional<Item>> equipped_;

	int gold_ = 0;

	// convenience: collect gold reward from enemy
	void collectRewardGold(int amount) { addGold(amount); }

	// helpers
	int findIndexByName(std::vector<Item>& container, const std::string& name);
	int findIndexByNameConst(const std::vector<Item>& container, const std::string& name) const;
};


#endif //SKUPINOVA_PRACE_2025_INVENTORY_H