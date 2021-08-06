/* DO NOT EDIT THIS FILE */
/* This file is autogenerated by the text-database code generator */

#include <touchgfx/TypedText.hpp>
#include <fonts/GeneratedFont.hpp>
#include <texts/TypedTextDatabase.hpp>

extern touchgfx::GeneratedFont& getFont_Asap_Regular_18_4bpp();
extern touchgfx::GeneratedFont& getFont_Asap_Regular_12_4bpp();
extern touchgfx::GeneratedFont& getFont_Asap_Regular_14_8bpp();
extern touchgfx::GeneratedFont& getFont_Asap_Regular_13_4bpp();

const touchgfx::Font* touchgfx_fonts[] =
{
    &(getFont_Asap_Regular_18_4bpp()),
    &(getFont_Asap_Regular_12_4bpp()),
    &(getFont_Asap_Regular_14_8bpp()),
    &(getFont_Asap_Regular_13_4bpp())
};

extern const touchgfx::TypedText::TypedTextData typedText_database_DEFAULT[];
extern const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[];

TEXT_LOCATION_FLASH_PRAGMA
const touchgfx::TypedText::TypedTextData typedText_database_DEFAULT[] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 2, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 0, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 3, touchgfx::LEFT, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR },
    { 1, touchgfx::CENTER, touchgfx::TEXT_DIRECTION_LTR }
};

TEXT_LOCATION_FLASH_PRAGMA
const touchgfx::TypedText::TypedTextData* const typedTextDatabaseArray[] TEXT_LOCATION_FLASH_ATTRIBUTE =
{
    typedText_database_DEFAULT
};

namespace TypedTextDatabase
{
const touchgfx::TypedText::TypedTextData* getInstance(touchgfx::LanguageId id)
{
    return typedTextDatabaseArray[id];
}

uint16_t getInstanceSize()
{
    return sizeof(typedText_database_DEFAULT) / sizeof(touchgfx::TypedText::TypedTextData);
}

const touchgfx::Font** getFonts()
{
    return touchgfx_fonts;
}

const touchgfx::Font* setFont(touchgfx::FontId fontId, const touchgfx::Font* font)
{
    const touchgfx::Font* old = touchgfx_fonts[fontId];
    touchgfx_fonts[fontId] = font;
    return old;
}

void resetFont(touchgfx::FontId fontId)
{
    switch (fontId)
    {
    case 0:
        touchgfx_fonts[0] = &(getFont_Asap_Regular_18_4bpp());
        break;
    case 1:
        touchgfx_fonts[1] = &(getFont_Asap_Regular_12_4bpp());
        break;
    case 2:
        touchgfx_fonts[2] = &(getFont_Asap_Regular_14_8bpp());
        break;
    case 3:
        touchgfx_fonts[3] = &(getFont_Asap_Regular_13_4bpp());
        break;
    }
}
}  // namespace TypedTextDatabase
