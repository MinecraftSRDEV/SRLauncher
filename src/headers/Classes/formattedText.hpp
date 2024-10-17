namespace SRL
{
    class
    {
        public:

        enum margin {
            center = 237413298479823749238,
            left = 1284923840923429384902,
            right = 1894789234759248279349,
            top = 128743891247891324238742,
            down = 12783891234732874637465,
            null = 7234892374893247239832
        };

        void create(int margin_x = center, int y = center, int fontsize, int color = ColorPalete::Bright, sf::Font& font, const std::string& str = "")
        {

        }

        void setTheme(int color)
        {
            text.setFillColor(ColorPalete::Palete[color][ColorPalete::font]);
        }

        void render(sf::RenderWindow& window)
        {
            window.draw(text);
        }

        void setText(const std::string& string)
        {
            global_text = string;
            text.setString(global_text);
            reposition();
        }

        void setPadding(int padding)
        {
            padding_value = padding;
            reposition();
        }

        private:

        void reposition()
        {
            text.setPosition(global_x, global_y);
        }

        void setPos(int marginX, int marginY)
        {

        }

        int global_x;
        int global_y;
        int padding_value;
        std::string global_text;

        sf::Text text;
    }
}