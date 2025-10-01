std::string tr(const std::string& key);

class uiElements {
public:

void createButton(sfg::Button& button, int posX, int posY, int sizeX, int sizeY, sf::Font& font, std::string input_text, bool block_state = false)
{
    button.create(posX, posY, sizeX, sizeY, font, input_text, block_state, theme_selected);
    UIButtons.emplace_back(&button);
}

void createMenagementButton(ManagementButton& button, int posX, int posY, sf::Font& font, sf::Texture& iconTx, std::string input_text, bool block_state = false)
{
    button.create(posX, posY, font, iconTx, input_text, block_state, theme_selected);
    UIMenagementButtons.emplace_back(&button);
}

void createCheckbox(sfg::Checkbox& checkbox, int sizeX, int sizeY, int posX, int posY, std::string text, int fontsize, sf::Font& font, bool defaultState)
{
    checkbox.create(sizeX, sizeY, posX, posY, text, fontsize, font, defaultState, theme_selected);
    UICheckboxes.emplace_back(&checkbox);
}

void createTextbox(sfg::Textbox& textbox, int x, int y, int size_x, int size_y, bool active_value, bool cursorVisible_value, sf::Font& font, int fontSize, std::string defaultText = "", bool readonly_default = false, std::string label_text = "")
{
    textbox.create(x, y, size_x, size_y, active_value, cursorVisible_value, font, fontSize, defaultText, readonly_default, label_text, theme_selected);
    UITextboxes.emplace_back(&textbox);
}

void createDropDownList(sfg::DropDownList& ddl, int sizeX, int sizeY, int posX, int posY, std::map <std::string, std::string>options, std::string default_selected, sf::Font& font, bool block_state = false)
{
    ddl.create(sizeX, sizeY, posX, posY, options, default_selected, font, block_state, theme_selected);
    UIDropDownLists.emplace_back(&ddl);
}

void createPasswordbox(sfg::Passwordbox& passwordbox, int x, int y, int size_x, int size_y, bool active_value, bool cursorVisible_value, sf::Font& font, int fontSize, std::string defaultText = "", bool readonly_default = false, std::string label_text = "")
{
    passwordbox.create(x, y, size_x, size_y, active_value, cursorVisible_value, font, fontSize, defaultText, readonly_default, label_text, theme_selected);
    UIPasswordboxes.emplace_back(&passwordbox);
}

void createTextfield(sfg::Textfield& textfield, int x, int y, int size_x, int size_y, sf::Font& fontset)
{
    textfield.create(x, y, size_x, size_y, fontset, theme_selected);
    UITextfields.emplace_back(&textfield);
}

void createTransparrentBg(sfg::TransparrentBackground& tpbg, int x, int y, int size_x, int size_y, bool outline = false)
{
    tpbg.create(x, y, size_x, size_y, outline, theme_selected);
    UITpBgs.emplace_back(&tpbg);
}

void setElementsTheme()
{
    for (auto* textItr : UITexts)
    {
        textItr->setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
    }
    for (auto* buttonItr : UIButtons)
    {
        buttonItr->setTheme(theme_selected);
    }
    for (auto* mngButtonItr : UIMenagementButtons)
    {
        mngButtonItr->setTheme(theme_selected);
    }
    for (auto* checkboxItr : UICheckboxes)
    {
        checkboxItr->setTheme(theme_selected);
    }
    for (auto* textboxItr : UITextboxes)
    {
        textboxItr->setTheme(theme_selected);
    }
    for (auto* ddlItr : UIDropDownLists)
    {
        ddlItr->setTheme(theme_selected);
    }
    for (auto* passwordboxItr : UIPasswordboxes)
    {
        passwordboxItr->setTheme(theme_selected);
    }
    for (auto* textfieldItr : UITextfields)
    {
        textfieldItr->setTheme(theme_selected);
        textfieldItr->applyTextColor(theme_selected);
    }
    for (auto* tpbgItr : UITpBgs)
    {
        tpbgItr->setTheme(theme_selected);
    }
}

void setElementsLanguage()
{
    for (auto* buttonItr : UIButtons)
    {
        if (tr(buttonItr->getID()) != "STRING NOT FOUND")
        buttonItr->setText(tr(buttonItr->getID()));
    }
    for (auto* checkboxItr : UICheckboxes)
    {
        if (tr(checkboxItr->getID()) != "STRING NOT FOUND")
        checkboxItr->changeText(tr(checkboxItr->getID()));
    }
    for (auto* textboxItr : UITextboxes)
    {
        if (tr(textboxItr->getID()) != "STRING NOT FOUND")
        textboxItr->setLabelText(tr(textboxItr->getID()));
    }
    for (auto* passwordboxItr : UIPasswordboxes)
    {
        if (tr(passwordboxItr->getID()) != "STRING NOT FOUND")
        passwordboxItr->setLabelText(tr(passwordboxItr->getID()));
    }
}

std::vector <sf::Text*> UITexts;
std::vector <sfg::Button*> UIButtons;
std::vector <ManagementButton*> UIMenagementButtons;
std::vector <sfg::Textbox*> UITextboxes;
std::vector <sfg::Checkbox*> UICheckboxes;
std::vector <sfg::DropDownList*> UIDropDownLists;
std::vector <sfg::Passwordbox*> UIPasswordboxes;
std::vector <sfg::Textfield*> UITextfields;
std::vector <sfg::TransparrentBackground*> UITpBgs;
};