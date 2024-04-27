#pragma once

#include "BasicWindow.h"
namespace Devkit {
    class AboutWindow : public BasicWindow {
    public:
        AboutWindow();

        void Render();

    private:
        bool m_bButtonFloNotFound;
        bool m_bButtonQbiNotFound;
    };
}// namespace Devkit
