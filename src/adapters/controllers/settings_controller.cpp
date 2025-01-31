#include "settings_controller.hpp"
#include <QDebug>
#include <QString>
#include "enum_utils.hpp"

using namespace application;
using application::setting_groups::SettingGroups;
using application::setting_keys::SettingKeys;
using application::utility::ApplicationSettings;

namespace adapters::controllers
{

SettingsController::SettingsController(ISettingsService* settingsService) :
    m_settingsService(settingsService)
{
    connect(m_settingsService, &ISettingsService::settingsLoaded, this,
            &SettingsController::initialiseSettings);

    connect(m_settingsService, &ISettingsService::settingChanged, this,
            &SettingsController::updateChangedSetting);
}

void SettingsController::setSetting(int key, const QVariant& value, int group)
{
    if(!keyIsValid(key) || !groupIsValid(group))
        return;

    auto keyAsEnum = static_cast<SettingKeys>(key);
    auto groupAsEnum = static_cast<SettingGroups>(group);
    m_settingsService->setSetting(keyAsEnum, value, groupAsEnum);
}

void SettingsController::resetSettingGroup(int group)
{
    if(!groupIsValid(group))
        return;

    auto groupAsEnum = static_cast<SettingGroups>(group);
    m_settingsService->resetSettingsGroupToDefault(groupAsEnum);
}

QQmlPropertyMap* SettingsController::getAppearanceSettings()
{
    return &m_appearanceSettingsMap;
}

QQmlPropertyMap* SettingsController::getGeneralSettings()
{
    return &m_generalSettingsMap;
}

QQmlPropertyMap* SettingsController::getShortcuts()
{
    return &m_shortcutsMap;
}

void SettingsController::updateChangedSetting(SettingKeys key, QVariant value,
                                              SettingGroups group)
{
    auto keyAsString = utility::getNameForEnumValue(key);

    switch(group)
    {
    case SettingGroups::Appearance:
        m_appearanceSettingsMap.insert(keyAsString, value.toString());
        break;
    case SettingGroups::General:
        m_generalSettingsMap.insert(keyAsString, value.toString());
        break;
    case SettingGroups::Shortcuts:
        m_shortcutsMap.insert(keyAsString, value.toString());
        break;
    case SettingGroups::SettingGroups_END:
        qCritical() << "Tried to update item of group SettingGroups_END";
        break;
    }
}

void SettingsController::initialiseSettings(ApplicationSettings settings)
{
    for(auto& elem : settings.appearanceSettings)
        m_appearanceSettingsMap.insert(elem.first, elem.second);

    for(auto& elem : settings.generalSettings)
        m_generalSettingsMap.insert(elem.first, elem.second);

    for(auto& elem : settings.shortcuts)
        m_shortcutsMap.insert(elem.first, elem.second);
}

bool SettingsController::keyIsValid(int key)
{
    int settingKeysEnd = static_cast<int>(SettingKeys::SettingKeys_END);
    if(key >= settingKeysEnd || key < 0)
    {
        qWarning() << QString("Invalid setting-key: %1").arg(key);
        return false;
    }

    return true;
}

bool SettingsController::groupIsValid(int group)
{
    int settingGroupsEnd = static_cast<int>(SettingGroups::SettingGroups_END);
    if(group >= settingGroupsEnd || group < 0)
    {
        qWarning() << QString("Invalid setting-group: %1").arg(group);
        return false;
    }

    return true;
}

}  // namespace adapters::controllers