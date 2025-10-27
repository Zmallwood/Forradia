//
// Copyright 2025 Andreas Åkerberg
// This code is licensed under MIT license
// (see LICENSE for details)
//

#pragma once

namespace Forradia::Theme0
{
    class Object
    {
      public:
        Object(StringView object_type_name)
            : m_type(Hash(object_type_name))
        {
        }

        auto GetType() const
        {
            return m_type;
        }

      private:
        int m_type{0};
    };
}