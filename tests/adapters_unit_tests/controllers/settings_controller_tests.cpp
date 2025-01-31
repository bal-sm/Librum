#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <QSignalSpy>
#include <QString>
#include "settings_controller.hpp"
#include "settings_service.hpp"

using namespace testing;
using namespace application;
using namespace adapters::controllers;

namespace tests::adapters
{

class SettingsServiceMock : public application::ISettingsService
{
public:
    MOCK_METHOD(QString, getSetting, (SettingKeys, SettingGroups), (override));
    MOCK_METHOD(void, setSetting, (SettingKeys, const QVariant&, SettingGroups),
                (override));
    MOCK_METHOD(void, resetSettingsGroupToDefault, (SettingGroups), (override));
    MOCK_METHOD(void, loadUserSettings, (const QString&, const QString&),
                (override));
    MOCK_METHOD(QString, getSettingsFilePath, (), (override));
    MOCK_METHOD(void, clearUserData, (), (override));
};

struct ASettingsController : public ::testing::Test
{
    ASettingsController()
    {
    }

    void SetUp() override
    {
        settingsController =
            std::make_unique<SettingsController>(&settingsServiceMock);
    }

    SettingsServiceMock settingsServiceMock;
    std::unique_ptr<SettingsController> settingsController;
};

TEST_F(ASettingsController, SucceedsSettingASetting)
{
    // Arrange
    int key = static_cast<int>(SettingKeys::DefaultZoom);
    QVariant value = 30;
    int group = static_cast<int>(SettingGroups::Appearance);

    // Expect
    EXPECT_CALL(settingsServiceMock, setSetting(_, _, _)).Times(1);


    // Act
    settingsController->setSetting(key, value, group);
}

TEST_F(ASettingsController, FailsSettingASettingIfKeyIsAboveBound)
{
    // Arrange
    int key = static_cast<int>(SettingKeys::SettingKeys_END) + 1;
    QVariant value = 30;
    int group = static_cast<int>(SettingGroups::Appearance);

    // Expect
    EXPECT_CALL(settingsServiceMock, setSetting(_, _, _)).Times(0);


    // Act
    settingsController->setSetting(key, value, group);
}

TEST_F(ASettingsController, FailsSettingASettingIfKeyIsBelowBound)
{
    // Arrange
    int key = -1;
    QVariant value = 30;
    int group = static_cast<int>(SettingGroups::Appearance);

    // Expect
    EXPECT_CALL(settingsServiceMock, setSetting(_, _, _)).Times(0);


    // Act
    settingsController->setSetting(key, value, group);
}

TEST_F(ASettingsController, FailsSettingASettingIfGroupIsAboveBound)
{
    // Arrange
    int key = static_cast<int>(SettingKeys::DefaultZoom);
    QVariant value = 30;
    int group = static_cast<int>(SettingGroups::SettingGroups_END) + 1;

    // Expect
    EXPECT_CALL(settingsServiceMock, setSetting(_, _, _)).Times(0);


    // Act
    settingsController->setSetting(key, value, group);
}

TEST_F(ASettingsController, FailsSettingASettingIfGroupIsBelowBound)
{
    // Arrange
    int key = static_cast<int>(SettingKeys::DefaultZoom);
    QVariant value = 30;
    int group = static_cast<int>(SettingGroups::SettingGroups_END) + 1;

    // Expect
    EXPECT_CALL(settingsServiceMock, setSetting(_, _, _)).Times(0);


    // Act
    settingsController->setSetting(key, value, group);
}

}  // namespace tests::adapters