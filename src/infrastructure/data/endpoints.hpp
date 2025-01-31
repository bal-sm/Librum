#pragma once
#include <QString>

namespace infrastructure::data
{
// clang-format off


inline const QString baseUrl { "https://librum-dev.azurewebsites.net" };    

// Authentication
inline const QString authenticationEndpoint { baseUrl + "/api/login" };
inline const QString registrationEndpoint { baseUrl + "/api/register" };

// Book storage
inline const QString bookCreationEndpoint { baseUrl + "/api/book" };
inline const QString bookUpdateEndpoint { baseUrl + "/api/book" };
inline const QString bookDeletionEndpoint { baseUrl + "/api/book" };
inline const QString booksMetadataGetEndpoint { baseUrl + "/api/book" };

// User storage
inline const QString userGetEndpoint { baseUrl + "/api/user" };
inline const QString userPatchEndpoint { baseUrl + "/api/user" };

// Tag storage
inline const QString tagUpdateEndpoint { baseUrl + "/api/tag" };
inline const QString tagDeletionEndpoint { baseUrl + "/api/tag" };


// clang-format on
}  // namespace infrastructure::data
