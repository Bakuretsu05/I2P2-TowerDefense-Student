#ifndef IMAGEBUTTON_HPP
#define IMAGEBUTTON_HPP
#include <allegro5/bitmap.h>
#include <functional>
#include <memory>
#include <string>

#include "Engine/IControl.hpp"
#include "../Image.hpp"

namespace Engine {
	/// <summary>
	/// A text input where we can toggle by clicking on it
	/// </summary>
	class TextInput: public Image, public IControl {
	protected:
		// Determines whether we are inputting
		bool mouseIn = false;

		// The smart pointer that points to bitmap for mouse-out display.
		std::shared_ptr<ALLEGRO_BITMAP> imgOut;

		// The smart pointer that points to bitmap for mouse-in display.
		std::shared_ptr<ALLEGRO_BITMAP> imgIn;

		// The callback function to call when text input clicked.
		std::function<void()> OnClickCallback;
	public:
        bool isInputting();

        void updateInput(int keyCode);

		/// <summary>
		/// Construct a image object.
		/// </summary>
		/// <param name="img">The mouse-out image path in 'Resource/images/'</param>
		/// <param name="imgIn">The mouse-in image path in 'Resource/images/'</param>
		/// <param name="x">X-coordinate.</param>
		/// <param name="y">Y-coordinate.</param>
		/// <param name="w">Width of the image, 0 indicates original size.</param>
		/// <param name="h">Height of the image, 0 indicates original size.</param>
		/// <param name="anchorX">The centerX of the object. (0, 0) means top-left, while (1, 0) means top-right.</param>
		/// <param name="anchorY">The centerY of the object. (0, 1) means bottom-left, while (1, 1) means bottom-right.</param>
		explicit TextInput(std::string img, std::string imgIn, float x, float y, float w = 0, float h = 0, float anchorX = 0, float anchorY = 0);

		/// <summary>
		/// Set the callback function when clicked.
		/// </summary>
		/// <param name="onClickCallback"></param>
		void SetOnClickCallback(std::function<void(void)> onClickCallback);

		/// <summary>
		/// Delegated from scene when mouse button down.
		/// </summary>
		/// <param name="button">The button pressed.</param>
		/// <param name="mx">Mouse x coordinate in window space.</param>
		/// <param name="my">Mouse y coordinate in window space.</param>
		void OnMouseDown(int button, int mx, int my) override;

		/// <summary>
		/// Delegated from scene when mouse move.
		/// </summary>
		/// <param name="mx">Mouse x coordinate in window space.</param>
		/// <param name="my">Mouse y coordinate in window space.</param>
		void OnMouseMove(int mx, int my) override;
    
    private:
		// Whether we are inputting
		bool Enabled = true;
        std::string textInput = "Player";
        IObject* textInputObject;

        struct ObjectData {
            std::string font;
            int fontSize;
            float x;
            float y;
            unsigned char r;
            unsigned char g;
            unsigned char b;
            unsigned char a;
            float anchorX;
            float anchorY;
        } textInputObjectData;
	};
}
#endif // IMAGEBUTTON_HPP
