class selectionListElement
{
    public:

    selectionListElement () {}

    struct listElementAttributes {
        int xPos = 0;
        int yPos = 0;
        int dX = 0;
        int dY = 0;

        int itr = 0;

        std::string name;
        std::string version;
    };

    listElementAttributes attributes;

    void create(int x, int y, int dx, int dy, int it_number, const std::string& name, const std::string& version, sf::Texture& icon_texture, sf::Font& font)
    {
        attributes.version = version;
        attributes.name = name;
        attributes.dX = dx;
        attributes.dY = dy;
        attributes.itr = it_number;

        iconTx = icon_texture;

        icon.setTexture(iconTx);

        body.setSize(sf::Vector2f(dx, dy));
        body.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::semitransparrent]);
        body.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
        body.setOutlineThickness(1);

        nameText.setString(name);
        nameText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
        nameText.setCharacterSize(26);
        nameText.setFont(font);

        versionText.setString("v." + version);
        versionText.setFillColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
        versionText.setCharacterSize(26);
        versionText.setFont(font);

        selectChkbox.create(30, 30, 0, 0, "", 0, font, false, theme_selected);

        reposition(x, y);
    }

    void reposition(int x, int y)
    {
        attributes.xPos = x;
        attributes.yPos = y;

        body.setPosition(x, y);

        selectChkbox.changePosition(x + 10, y + 15);

        icon.setPosition(sf::Vector2f(body.getPosition().x + 70, body.getPosition().y + 1));
        nameText.setPosition(body.getPosition().x + 150, body.getPosition().y + 5);
        versionText.setPosition(body.getPosition().x + (50 + (nameText.getLocalBounds().width + nameText.getPosition().x)), body.getPosition().y + 5);
    }

    void render(sf::RenderWindow& window)
    {
        if (body.getPosition().y >= 115 and body.getPosition().y <= 600)
        {
            window.draw(body);
            selectChkbox.render(window);
            window.draw(icon);
            window.draw(nameText);
            window.draw(versionText);
        }
    }

    void update(sf::Vector2f& mouse)
    {
        selectChkbox.update(mouse);
        if (body.getGlobalBounds().contains(mouse))
        {
            body.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::blocked]);
        }
        else
        {
            body.setOutlineColor(ColorPalete::Palete[theme_selected][ColorPalete::font]);
        }
    }

    sfg::Checkbox selectChkbox;

    private:

    sf::RectangleShape body;
    sf::Sprite icon;
    sf::Texture iconTx;
    sf::Text nameText;
    sf::Text versionText;
    
};