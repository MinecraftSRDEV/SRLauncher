class SteamGuardAuthClass {
public:

SteamGuardAuthClass () {}

void create(int x, int y, sf::Font& font, int color = ColorPalete::Bright)
{
    colorSet = color;

    background.setSize(sf::Vector2f(500, 340));
    background.setOutlineThickness(1);
    background.setPosition(x, y);

    confirm_button.create(x + 100, y + 280, 300, 40, font, "Confirm", true, color);
    confirm_button.setFunction(confirm_function);

    code_textbox.create(x + 100, y + 100, 300, 60, true, true, font, 56, "", false, "Steam Guard code", color);
}

void setTheme(int color)
{
    background.setFillColor(ColorPalete::Palete[color][ColorPalete::semitransparrent]);
    background.setOutlineColor(ColorPalete::Palete[color][ColorPalete::outline]);
    confirm_button.setTheme(color);
    code_textbox.setTheme(color);
}

void render(sf::RenderWindow& window)
{
    window.draw(background);
    confirm_button.render(window);
    code_textbox.render(window);
}

void update(sf::Vector2f mouse)
{
    if (code_textbox.getText().length() > 0 && code_textbox.getText().length() < 6)
    {
        confirm_button.setBlockState(false);
    }
    else
    {
        confirm_button.setBlockState(true);
    }
    confirm_button.update(mouse);
    code_textbox.update(mouse);

    guard_code = code_textbox.getText();
}

void event(sf::Event& event)
{
    code_textbox.handleEvent(event);
}

static void confirm_function()
{
    send_guard_code = true;
    display_guard_window = false;
}

private:

int colorSet;

sf::RectangleShape background;

sfg::Button confirm_button;
sfg::Textbox code_textbox;
};