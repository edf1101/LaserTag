/*
 * Created by Ed Fillingham on 19/04/2024.
 *
 * This class is a menu that allows the user to select a gun.
*/

#include "GunMenu.h"
#include "../../../LaserTag.h"

Menus::GunMenu::GunMenu(MenuManager *myMenuManager) {
  // constructor for the class
  setRotaryMax(4); // Set the maximum number of buttons in the sub menu
  menuManager = myMenuManager;
  fetchGunsInUse();

  // Set the callback functions for the sub menu
  std::function<void(int)> changeCallback =
          std::bind(&GunMenu::subMenuCounterChanged, this, std::placeholders::_1);
  subMenu.setCounterChangedCallback(changeCallback);
  std::function<void(int)> pressCallback =
          std::bind(&GunMenu::subMenuCounterPressed, this, std::placeholders::_1);
  subMenu.setCounterPressedCallback(pressCallback);

  subMenu.draw(true);

  // set the weapons manager callback to update this menu if the guns available change
  WeaponsManager::setUpdateMenuCallback(std::bind(&GunMenu::fetchGunsInUse, this));
}

void Menus::GunMenu::display(bool force) {
  subMenu.draw(force); // draw the sub menu

  // draw the gun details
  gunImage.draw(force);
  gunName.draw(force);
  gunAmmo.draw(force);
  gunMags.draw(force);
  gunFireType.draw(force);
  gunFireRate.draw(force);
  gunDamage.draw(force);
  gunSuppressed.draw(force);

}

void Menus::GunMenu::onRotaryTurned(int change) {
  // When the rotary encoder is turned pass it onto the submenu

  Menu::onRotaryTurned(change);
  subMenu.onRotaryTurned(rotaryCounter);

  subMenu.draw(false); // update the menu
}

void Menus::GunMenu::onRotaryPressed() {
  // When the rotary encoder is pressed pass it onto the submenu
  subMenu.onRotaryPressed();
}

void Menus::GunMenu::resetMenu() {
  // Reset the menu when leaving it

  Menu::resetMenu();
  subMenu.reset();

  // reset gun info text
  Weapons::Gun currentGun = gunsInUse[0];
  int fireRate = (int) round(1.0 / ((float) currentGun.getFireSpeed() / 1000.0));
  std::string suppressed = currentGun.getSuppressed() ? "TRUE" : "FALSE";
  gunImage.setImage(currentGun.getImage());
  gunName.setText("Name: " + currentGun.getName());
  gunAmmo.setText("Ammo: " + std::to_string(currentGun.getAmmoRemaining()));
  gunMags.setText("Mags: " + std::to_string(currentGun.getMagsRemaining()));
  gunFireType.setText("Type: " + currentGun.getFireType());
  gunFireRate.setText("Speed: " + std::to_string(fireRate) + " bullets/s");
  gunDamage.setText("Damage: " + std::to_string(currentGun.getDamage()));
  gunSuppressed.setText("Suppressed?: " + suppressed);
}

void Menus::GunMenu::init(SideDisplay *sideDisplay, Menu *previousMenu) {
  // Initialise the menu

  Menus::Menu::init(sideDisplay);

  // set up the widgets init functions
  subMenu.init(sideDisplay, menuManager, previousMenu);
  gunImage.init(sideDisplay);
  gunName.init(sideDisplay);
  gunAmmo.init(sideDisplay);
  gunMags.init(sideDisplay);
  gunFireType.init(sideDisplay);
  gunFireRate.init(sideDisplay);
  gunDamage.init(sideDisplay);
  gunSuppressed.init(sideDisplay);

}


void Menus::GunMenu::fetchGunsInUse() {
  // Fetch the guns in use and save them in the gunsInUse vector

  gunsInUse = WeaponsManager::getAllGuns();
  subMenu.setMaxSubMenuCounter(gunsInUse.size() - 1);
}

void Menus::GunMenu::subMenuCounterChanged(int item) {
  // When the sub menu counter changes update the gun info text

  Weapons::Gun currentGun = gunsInUse[item];
  int fireRate = (int) round(1.0 / ((float) currentGun.getFireSpeed() / 1000.0));
  std::string suppressed = currentGun.getSuppressed() ? "TRUE" : "FALSE";
  gunImage.setImage(currentGun.getImage());
  gunName.setText("Name: " + currentGun.getName());
  gunAmmo.setText("Ammo: " + std::to_string(currentGun.getAmmoRemaining()));
  gunMags.setText("Mags: " + std::to_string(currentGun.getMagsRemaining()));
  gunFireType.setText("Type: " + currentGun.getFireType());
  gunFireRate.setText("Speed: " + std::to_string(fireRate) + " bullets/s");
  gunDamage.setText("Damage: " + std::to_string(currentGun.getDamage()));
  gunSuppressed.setText("Suppressed?: " + suppressed);

  display(false);
}

void Menus::GunMenu::subMenuCounterPressed(int item) {
  // Called when the select button in submenu is pressed

  // set the gun to the selected gun
  if (WeaponsManager::getGunsSwappable()) // only swap if we are allowed to
    LaserTag::getPlayer()->swapGun(gunsInUse[item].getName());

  menuManager->switchMenu(parentMenu); // switch back to the parent menu
}


