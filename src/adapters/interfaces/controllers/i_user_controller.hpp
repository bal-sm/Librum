#include <QObject>
#include "user_tags_model.hpp"
#pragma once

namespace adapters
{

/**
 * The UserController class is exposed to the UI code and thus is the
 * "entry point" to the application's backend for user operations. It acts as a
 * layer of abstraction which maps the user data to a format usable for the
 * application.
 */
class IUserController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ getFirstName WRITE setFirstName NOTIFY
                   firstNameChanged)
    Q_PROPERTY(QString lastName READ getLastName WRITE setLastName NOTIFY
                   lastNameChanged)
    Q_PROPERTY(QString email READ getEmail WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(QString profilePicture READ getProfilePicture WRITE
                   setProfilePicture NOTIFY profilePictureChanged)
    Q_PROPERTY(adapters::data_models ::UserTagsModel* tagsModel READ
                   getUserTagsModel CONSTANT)

public:
    virtual ~IUserController() noexcept = default;

    Q_INVOKABLE virtual void loadUser() = 0;

    Q_INVOKABLE virtual QString getTagUuidForName(QString name) = 0;
    Q_INVOKABLE virtual QString addTag(const QString& name) = 0;
    Q_INVOKABLE virtual bool deleteTag(const QString& uuid) = 0;
    Q_INVOKABLE virtual bool renameTag(const QString& uuid,
                                       const QString& newName) = 0;

    virtual QString getFirstName() = 0;
    virtual void setFirstName(const QString& newFirstName) = 0;

    virtual QString getLastName() = 0;
    virtual void setLastName(const QString& newLastName) = 0;

    virtual QString getEmail() = 0;
    virtual void setEmail(const QString& newEmail) = 0;

    virtual QString getProfilePicture() const = 0;
    virtual void setProfilePicture(const QString& path) = 0;

    virtual data_models::UserTagsModel* getUserTagsModel() = 0;

signals:
    void finishedLoadingUser(bool success);
    void firstNameChanged();
    void lastNameChanged();
    void emailChanged();
    void profilePictureChanged();
};

}  // namespace adapters