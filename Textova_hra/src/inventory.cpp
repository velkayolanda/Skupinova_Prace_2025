//
// Created by Jar Jar Banton on 17. 11. 2025.
//

#include "inventory.h"
#include <iostream>
#include <algorithm>
// loot system: global Item type and loot helpers
#include "loot.h"


inventory::inventory(int maxWeapons, int maxPotions, int maxArmors, int equipSlots)
	: maxWeapons_(maxWeapons), maxPotions_(maxPotions), maxArmors_(maxArmors), equipSlots_(equipSlots), equipped_(equipSlots), gold_(0) {}

int inventory::findIndexByName(std::vector<Item>& container, const std::string& name) {
	for (size_t i = 0; i < container.size(); ++i) {
		if (container[i].name == name) return static_cast<int>(i);
	}
	return -1;
}

int inventory::findIndexByNameConst(const std::vector<Item>& container, const std::string& name) const {
	for (size_t i = 0; i < container.size(); ++i) {
		if (container[i].name == name) return static_cast<int>(i);
	}
	return -1;
}

bool inventory::addItem(const Item& item) {
	switch (item.type) {
		case ItemType::Weapon: {
			int idx = findIndexByName(weapons_, item.name);
			if (idx >= 0) {
				weapons_[idx].quantity += item.quantity;
				return true;
			}
			if (static_cast<int>(weapons_.size()) < maxWeapons_) {
				weapons_.push_back(item);
				return true;
			}
			return false; // no weapon slot
		}
		case ItemType::Armor: {
			int idx = findIndexByName(armors_, item.name);
			if (idx >= 0) {
				armors_[idx].quantity += item.quantity;
				return true;
			}
			if (static_cast<int>(armors_.size()) < maxArmors_) {
				armors_.push_back(item);
				return true;
			}
			return false; // no armor slot
		}
		case ItemType::Potion: {
			int idx = findIndexByName(potions_, item.name);
			if (idx >= 0) {
				potions_[idx].quantity += item.quantity;
				return true;
			}
			if (static_cast<int>(potions_.size()) < maxPotions_) {
				potions_.push_back(item);
				return true;
			}
			return false; // no potion slot
		}
		case ItemType::Misc: {
			int idx = findIndexByName(misc_, item.name);
			if (idx >= 0) {
				misc_[idx].quantity += item.quantity;
			} else {
				misc_.push_back(item);
			}
			return true;
		}
		default:
			return false;
	}
}
bool inventory::removeItem(const std::string& name, int qty) {
	// weapons
	int idx = findIndexByName(weapons_, name);
	if (idx >= 0) {
		if (weapons_[idx].quantity > qty) {
			weapons_[idx].quantity -= qty;
			return true;
		}
		// remove entirely
		weapons_.erase(weapons_.begin() + idx);
		return true;
	}
	idx = findIndexByName(potions_, name);
	if (idx >= 0) {
		if (potions_[idx].quantity > qty) {
			potions_[idx].quantity -= qty;
			return true;
		}
		potions_.erase(potions_.begin() + idx);
		return true;
	}
	idx = findIndexByName(misc_, name);
	if (idx >= 0) {
		if (misc_[idx].quantity > qty) {
			misc_[idx].quantity -= qty;
			return true;
		}
		misc_.erase(misc_.begin() + idx);
		return true;
	}
	return false;
}

bool inventory::equipItem(const std::string& name, int slot) {
	if (slot < 0 || slot >= equipSlots_) return false;
	if (equipped_[slot].has_value()) return false; // slot occupied

	// prefer weapons
	int idx = findIndexByName(weapons_, name);
	if (idx >= 0) {
		Item item = weapons_[idx];
		// equip a single quantity
		Item single{item.name, item.type, 1};
		equipped_[slot] = single;
		if (weapons_[idx].quantity > 1) weapons_[idx].quantity -= 1;
		else weapons_.erase(weapons_.begin() + idx);
		return true;
	}

	// allow equipping misc items as well
	// try armor next
	idx = findIndexByName(armors_, name);
	if (idx >= 0) {
		Item item = armors_[idx];
		Item single{item.name, item.type, 1};
		equipped_[slot] = single;
		if (armors_[idx].quantity > 1) armors_[idx].quantity -= 1;
		else armors_.erase(armors_.begin() + idx);
		return true;
	}

	idx = findIndexByName(misc_, name);
	if (idx >= 0) {
		Item item = misc_[idx];
		Item single{item.name, item.type, 1};
		equipped_[slot] = single;
		if (misc_[idx].quantity > 1) misc_[idx].quantity -= 1;
		else misc_.erase(misc_.begin() + idx);
		return true;
	}

	return false; // not found
}

bool inventory::unequip(int slot) {
	if (slot < 0 || slot >= equipSlots_) return false;
	if (!equipped_[slot].has_value()) return false;

	Item it = equipped_[slot].value();
	// try to add back to inventory; if it fails, keep equipped
	if (!addItem(it)) return false;

	equipped_[slot].reset();
	return true;
}

void inventory::addGold(int amount) {
	if (amount >= 0) gold_ += amount;
	else spendGold(-amount);
}

bool inventory::spendGold(int amount) {
	if (amount < 0) return false;
	if (gold_ >= amount) {
		gold_ -= amount;
		return true;
	}
	return false;
}

int inventory::getGold() const {
	return gold_;
}

void inventory::display() const {
	std::cout << "===== INVENTORY =====\n";
	std::cout << "Gold: " << gold_ << "\n\n";

	std::cout << "Equipped (slots: " << equipSlots_ << "):\n";
	for (int i = 0; i < equipSlots_; ++i) {
		std::cout << " [" << i << "] ";
		if (equipped_[i].has_value()) {
			const Item &it = equipped_[i].value();
			std::cout << it.name << " (" << (it.quantity) << ")";
		} else {
			std::cout << "(empty)";
		}
		std::cout << "\n";
	}
	std::cout << "\nWeapons (slots: " << maxWeapons_ << "):\n";
	if (weapons_.empty()) std::cout << "  (none)\n";
	for (const auto &w: weapons_) {
		std::cout << "  - " << w.name << " x" << w.quantity << "\n";
	}

	std::cout << "\nArmors (slots: " << maxArmors_ << "):\n";
	if (armors_.empty()) std::cout << "  (none)\n";
	for (const auto &a: armors_) {
		std::cout << "  - " << a.name << " x" << a.quantity << "\n";
	}

	std::cout << "\nPotions (slots: " << maxPotions_ << "):\n";
	if (potions_.empty()) std::cout << "  (none)\n";
	for (const auto &p: potions_) {
		std::cout << "  - " << p.name << " x" << p.quantity << "\n";
	}

	std::cout << "\nMisc: \n";
	if (misc_.empty()) std::cout << "  (none)\n";
	for (const auto &m: misc_) {
		std::cout << "  - " << m.name << " x" << m.quantity << "\n";
	}

	std::cout << "=====================\n";
}

bool inventory::addLoot(const ::Item& loot) {
	// map loot.type (string) to ItemType
	std::string t = loot.type;
	std::transform(t.begin(), t.end(), t.begin(), ::tolower);

	// treasure/trezor -> add gold directly
	if (t == "treasure" || t == "trezor" || t == "treasure") {
		// use loot.value as gold amount
		addGold(loot.value);
		return true;
	}

	inventory::ItemType mappedType = inventory::ItemType::Misc; // default
	// translate known Czech/English type names
	if (t == "zbrane" || t == "weapon" || t == "weapons") {
		mappedType = inventory::ItemType::Weapon;
	} else if (t == "potecka" || t == "potion" || t == "potions") {
		mappedType = inventory::ItemType::Potion;
	} else if (t == "armour" || t == "armor" || t == "armour") {
		mappedType = inventory::ItemType::Armor;
	} else {
		mappedType = inventory::ItemType::Misc;
	}

	// create inventory item with quantity 1
	Item invItem(loot.name, mappedType, 1);
	return addItem(invItem);
}

bool inventory::addLoot(const std::vector<::Item>& lootVec) {
	bool allAdded = true;
	for (const auto &l : lootVec) {
		if (!addLoot(l)) allAdded = false;
	}
	return allAdded;
}
