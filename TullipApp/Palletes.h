/**
 * @file Palletes.h
 * @brief Defines color palettes for different themes.
 */

#ifndef PALLETES_H_
#define PALLETES_H_

#include <QPalette>
#include <QColor>

 // -------------------- Material --------------------

inline QPalette MaterialLight()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#FFFFFF"));
    p.setColor(QPalette::WindowText, QColor("#000000"));
    p.setColor(QPalette::Base, QColor("#FAFAFA"));
    p.setColor(QPalette::AlternateBase, QColor("#EEEEEE"));
    p.setColor(QPalette::ToolTipBase, QColor("#FFFFFF"));
    p.setColor(QPalette::ToolTipText, QColor("#000000"));
    p.setColor(QPalette::Text, QColor("#000000"));
    p.setColor(QPalette::Button, QColor("#E0E0E0"));
    p.setColor(QPalette::ButtonText, QColor("#000000"));
    p.setColor(QPalette::BrightText, Qt::red);
    p.setColor(QPalette::Link, QColor("#1E88E5"));
    p.setColor(QPalette::Highlight, QColor("#90CAF9"));
    p.setColor(QPalette::HighlightedText, QColor("#000000"));
    p.setColor(QPalette::PlaceholderText, QColor("#666666"));
    return p;
}

inline QPalette MaterialDark()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor(53, 53, 53));
    p.setColor(QPalette::WindowText, Qt::white);
    p.setColor(QPalette::Base, QColor(25, 25, 25));
    p.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    p.setColor(QPalette::ToolTipBase, Qt::white);
    p.setColor(QPalette::ToolTipText, Qt::white);
    p.setColor(QPalette::Text, Qt::white);
    p.setColor(QPalette::Button, QColor(53, 53, 53));
    p.setColor(QPalette::ButtonText, Qt::white);
    p.setColor(QPalette::BrightText, Qt::red);
    p.setColor(QPalette::Link, QColor(42, 130, 218));
    p.setColor(QPalette::Highlight, QColor(42, 130, 218));
    p.setColor(QPalette::HighlightedText, Qt::black);
    p.setColor(QPalette::PlaceholderText, QColor("#BBBBBB"));
    return p;
}

// ------------------ Solarized ------------------

inline QPalette SolarizedLight()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#FDF6E3"));
    p.setColor(QPalette::WindowText, QColor("#657B83"));
    p.setColor(QPalette::Base, QColor("#EEE8D5"));
    p.setColor(QPalette::AlternateBase, QColor("#EDE6CE"));
    p.setColor(QPalette::ToolTipBase, QColor("#FDF6E3"));
    p.setColor(QPalette::ToolTipText, QColor("#657B83"));
    p.setColor(QPalette::Text, QColor("#657B83"));
    p.setColor(QPalette::Button, QColor("#DCD7B8"));
    p.setColor(QPalette::ButtonText, QColor("#657B83"));
    p.setColor(QPalette::BrightText, Qt::red);
    p.setColor(QPalette::Link, QColor("#268BD2"));
    p.setColor(QPalette::Highlight, QColor("#B58900"));
    p.setColor(QPalette::HighlightedText, QColor("#FDF6E3"));
    p.setColor(QPalette::PlaceholderText, QColor("#586E75"));
    return p;
}

inline QPalette SolarizedDark()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#002B36"));
    p.setColor(QPalette::WindowText, QColor("#839496"));
    p.setColor(QPalette::Base, QColor("#073642"));
    p.setColor(QPalette::AlternateBase, QColor("#00212B"));
    p.setColor(QPalette::ToolTipBase, QColor("#002B36"));
    p.setColor(QPalette::ToolTipText, QColor("#839496"));
    p.setColor(QPalette::Text, QColor("#839496"));
    p.setColor(QPalette::Button, QColor("#002B36"));
    p.setColor(QPalette::ButtonText, QColor("#839496"));
    p.setColor(QPalette::BrightText, Qt::red);
    p.setColor(QPalette::Link, QColor("#268BD2"));
    p.setColor(QPalette::Highlight, QColor("#586E75"));
    p.setColor(QPalette::HighlightedText, QColor("#002B36"));
    p.setColor(QPalette::PlaceholderText, QColor("#BBBBBB"));
    return p;
}

// --------------------- Sepia ---------------------

inline QPalette SepiaLight()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#FBF3E4"));
    p.setColor(QPalette::WindowText, QColor("#5B4636"));
    p.setColor(QPalette::Base, QColor("#F5E9D4"));
    p.setColor(QPalette::AlternateBase, QColor("#EEE1C7"));
    p.setColor(QPalette::ToolTipBase, QColor("#FBF3E4"));
    p.setColor(QPalette::ToolTipText, QColor("#5B4636"));
    p.setColor(QPalette::Text, QColor("#5B4636"));
    p.setColor(QPalette::Button, QColor("#E4D6C3"));
    p.setColor(QPalette::ButtonText, QColor("#5B4636"));
    p.setColor(QPalette::BrightText, QColor("#FF0000"));
    p.setColor(QPalette::Link, QColor("#8B4513"));
    p.setColor(QPalette::Highlight, QColor("#CBA071"));
    p.setColor(QPalette::HighlightedText, QColor("#FBF3E4"));
    p.setColor(QPalette::PlaceholderText, QColor("#8A6F5C"));
    return p;
}

inline QPalette SepiaDark()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#3E2F25"));
    p.setColor(QPalette::WindowText, QColor("#D6C1AA"));
    p.setColor(QPalette::Base, QColor("#362A21"));
    p.setColor(QPalette::AlternateBase, QColor("#3E2F25"));
    p.setColor(QPalette::ToolTipBase, QColor("#D6C1AA"));
    p.setColor(QPalette::ToolTipText, QColor("#3E2F25"));
    p.setColor(QPalette::Text, QColor("#D6C1AA"));
    p.setColor(QPalette::Button, QColor("#3E2F25"));
    p.setColor(QPalette::ButtonText, QColor("#D6C1AA"));
    p.setColor(QPalette::BrightText, QColor("#FF0000"));
    p.setColor(QPalette::Link, QColor("#E0C097"));
    p.setColor(QPalette::Highlight, QColor("#A2836E"));
    p.setColor(QPalette::HighlightedText, QColor("#362A21"));
    p.setColor(QPalette::PlaceholderText, QColor("#BBBBBB"));
    return p;
}

// ---------------- Ocean Breeze ----------------

inline QPalette OceanBreezeLight()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#E0F7FA"));
    p.setColor(QPalette::WindowText, QColor("#006064"));
    p.setColor(QPalette::Base, QColor("#B2EBF2"));
    p.setColor(QPalette::AlternateBase, QColor("#80DEEA"));
    p.setColor(QPalette::ToolTipBase, QColor("#E0F7FA"));
    p.setColor(QPalette::ToolTipText, QColor("#006064"));
    p.setColor(QPalette::Text, QColor("#006064"));
    p.setColor(QPalette::Button, QColor("#4DD0E1"));
    p.setColor(QPalette::ButtonText, QColor("#006064"));
    p.setColor(QPalette::BrightText, QColor("#FF5252"));
    p.setColor(QPalette::Link, QColor("#00838F"));
    p.setColor(QPalette::Highlight, QColor("#4DD0E1"));
    p.setColor(QPalette::HighlightedText, QColor("#E0F7FA"));
    p.setColor(QPalette::PlaceholderText, QColor("#004D40"));
    return p;
}

inline QPalette OceanBreezeDark()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#004D40"));
    p.setColor(QPalette::WindowText, QColor("#B2DFDB"));
    p.setColor(QPalette::Base, QColor("#00332B"));
    p.setColor(QPalette::AlternateBase, QColor("#004D40"));
    p.setColor(QPalette::ToolTipBase, QColor("#B2DFDB"));
    p.setColor(QPalette::ToolTipText, QColor("#004D40"));
    p.setColor(QPalette::Text, QColor("#B2DFDB"));
    p.setColor(QPalette::Button, QColor("#004D40"));
    p.setColor(QPalette::ButtonText, QColor("#B2DFDB"));
    p.setColor(QPalette::BrightText, QColor("#FF5252"));
    p.setColor(QPalette::Link, QColor("#4DD0E1"));
    p.setColor(QPalette::Highlight, QColor("#26A69A"));
    p.setColor(QPalette::HighlightedText, QColor("#00332B"));
    p.setColor(QPalette::PlaceholderText, QColor("#BBBBBB"));
    return p;
}

// --------------- Sunset Glow ------------------

inline QPalette SunsetGlowLight()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#FFF3E0"));
    p.setColor(QPalette::WindowText, QColor("#BF360C"));
    p.setColor(QPalette::Base, QColor("#FFE0B2"));
    p.setColor(QPalette::AlternateBase, QColor("#FFD180"));
    p.setColor(QPalette::ToolTipBase, QColor("#FFF3E0"));
    p.setColor(QPalette::ToolTipText, QColor("#BF360C"));
    p.setColor(QPalette::Text, QColor("#BF360C"));
    p.setColor(QPalette::Button, QColor("#FFB74D"));
    p.setColor(QPalette::ButtonText, QColor("#BF360C"));
    p.setColor(QPalette::BrightText, QColor("#FF0000"));
    p.setColor(QPalette::Link, QColor("#F57C00"));
    p.setColor(QPalette::Highlight, QColor("#FFCC80"));
    p.setColor(QPalette::HighlightedText, QColor("#FFF3E0"));
    p.setColor(QPalette::PlaceholderText, QColor("#8E4400"));
    return p;
}

inline QPalette SunsetGlowDark()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#4E342E"));
    p.setColor(QPalette::WindowText, QColor("#FFE0B2"));
    p.setColor(QPalette::Base, QColor("#3E2723"));
    p.setColor(QPalette::AlternateBase, QColor("#4E342E"));
    p.setColor(QPalette::ToolTipBase, QColor("#FFE0B2"));
    p.setColor(QPalette::ToolTipText, QColor("#4E342E"));
    p.setColor(QPalette::Text, QColor("#FFE0B2"));
    p.setColor(QPalette::Button, QColor("#4E342E"));
    p.setColor(QPalette::ButtonText, QColor("#FFE0B2"));
    p.setColor(QPalette::BrightText, QColor("#FF0000"));
    p.setColor(QPalette::Link, QColor("#FFCC80"));
    p.setColor(QPalette::Highlight, QColor("#FFB74D"));
    p.setColor(QPalette::HighlightedText, QColor("#3E2723"));
    p.setColor(QPalette::PlaceholderText, QColor("#BBBBBB"));
    return p;
}

// -------------- Forest Shade -----------------

inline QPalette ForestShadeLight()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#E8F5E9"));
    p.setColor(QPalette::WindowText, QColor("#1B5E20"));
    p.setColor(QPalette::Base, QColor("#C8E6C9"));
    p.setColor(QPalette::AlternateBase, QColor("#A5D6A7"));
    p.setColor(QPalette::ToolTipBase, QColor("#E8F5E9"));
    p.setColor(QPalette::ToolTipText, QColor("#1B5E20"));
    p.setColor(QPalette::Text, QColor("#1B5E20"));
    p.setColor(QPalette::Button, QColor("#66BB6A"));
    p.setColor(QPalette::ButtonText, QColor("#1B5E20"));
    p.setColor(QPalette::BrightText, QColor("#FF0000"));
    p.setColor(QPalette::Link, QColor("#2E7D32"));
    p.setColor(QPalette::Highlight, QColor("#A5D6A7"));
    p.setColor(QPalette::HighlightedText, QColor("#E8F5E9"));
    p.setColor(QPalette::PlaceholderText, QColor("#4F7942"));
    return p;
}

inline QPalette ForestShadeDark()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#1B5E20"));
    p.setColor(QPalette::WindowText, QColor("#C8E6C9"));
    p.setColor(QPalette::Base, QColor("#0D3C11"));
    p.setColor(QPalette::AlternateBase, QColor("#1B5E20"));
    p.setColor(QPalette::ToolTipBase, QColor("#C8E6C9"));
    p.setColor(QPalette::ToolTipText, QColor("#1B5E20"));
    p.setColor(QPalette::Text, QColor("#C8E6C9"));
    p.setColor(QPalette::Button, QColor("#1B5E20"));
    p.setColor(QPalette::ButtonText, QColor("#C8E6C9"));
    p.setColor(QPalette::BrightText, QColor("#FF0000"));
    p.setColor(QPalette::Link, QColor("#81C784"));
    p.setColor(QPalette::Highlight, QColor("#4CAF50"));
    p.setColor(QPalette::HighlightedText, QColor("#0D3C11"));
    p.setColor(QPalette::PlaceholderText, QColor("#BBBBBB"));
    return p;
}

// ------------- Desert Sand -------------------

inline QPalette DesertSandLight()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#FFF8E1"));
    p.setColor(QPalette::WindowText, QColor("#5D4037"));
    p.setColor(QPalette::Base, QColor("#FFECB3"));
    p.setColor(QPalette::AlternateBase, QColor("#FFE082"));
    p.setColor(QPalette::ToolTipBase, QColor("#FFF8E1"));
    p.setColor(QPalette::ToolTipText, QColor("#5D4037"));
    p.setColor(QPalette::Text, QColor("#5D4037"));
    p.setColor(QPalette::Button, QColor("#FFD54F"));
    p.setColor(QPalette::ButtonText, QColor("#5D4037"));
    p.setColor(QPalette::BrightText, QColor("#FF0000"));
    p.setColor(QPalette::Link, QColor("#FFA000"));
    p.setColor(QPalette::Highlight, QColor("#FFE082"));
    p.setColor(QPalette::HighlightedText, QColor("#FFF8E1"));
    p.setColor(QPalette::PlaceholderText, QColor("#8D6E63"));
    return p;
}

inline QPalette DesertSandDark()
{
    QPalette p;
    p.setColor(QPalette::Window, QColor("#5D4037"));
    p.setColor(QPalette::WindowText, QColor("#FFECB3"));
    p.setColor(QPalette::Base, QColor("#3E2723"));
    p.setColor(QPalette::AlternateBase, QColor("#5D4037"));
    p.setColor(QPalette::ToolTipBase, QColor("#FFECB3"));
    p.setColor(QPalette::ToolTipText, QColor("#5D4037"));
    p.setColor(QPalette::Text, QColor("#FFECB3"));
    p.setColor(QPalette::Button, QColor("#5D4037"));
    p.setColor(QPalette::ButtonText, QColor("#FFECB3"));
    p.setColor(QPalette::BrightText, QColor("#FF0000"));
    p.setColor(QPalette::Link, QColor("#FFD54F"));
    p.setColor(QPalette::Highlight, QColor("#FFB74D"));
    p.setColor(QPalette::HighlightedText, QColor("#3E2723"));
    p.setColor(QPalette::PlaceholderText, QColor("#BBBBBB"));
    return p;
}


#endif // PALLETES_H_