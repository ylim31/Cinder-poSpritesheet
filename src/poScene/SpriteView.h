//
//  Sprite.h
//  ForestFriends
//
//  Created by bruce on 9/11/14.
//
//

#pragma once


#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Texture.h"
#include "cinder/Json.h"

#include "poScene/View.h"
#include "poSpritesheet.h"
#include "poSpritesheetAnimation.h"

namespace po
{
	namespace scene
	{
		class SpriteView;
		typedef std::shared_ptr<SpriteView> SpriteViewRef;

		class SpriteView
			: public View
		{
			public:
				struct SpriteDataJson {
					std::vector<ci::gl::TextureRef> textures;
					std::vector<ci::JsonTree>       jsonFiles;
				};

				struct SpriteDataXml {
					std::vector<ci::gl::TextureRef> textures;
					std::vector<ci::XmlTree>        xmlFiles;
				};

				// using single-texture spritesheets
				static SpriteViewRef create( ci::gl::TextureRef texture, ci::JsonTree json );
				static SpriteViewRef create( ci::gl::TextureRef texture, ci::XmlTree xml );

				// using Multipacked texture spritesheets
				static SpriteViewRef create( std::vector<ci::gl::TextureRef>& textures, std::vector<ci::JsonTree>& data );
				static SpriteViewRef create( std::vector<ci::gl::TextureRef>& textures, std::vector<ci::XmlTree>& data );

				//	using a spritesheet
				static SpriteViewRef create( po::SpritesheetRef spriteSheet );

				//  using spritedata object
				static SpriteViewRef create( SpriteDataJson& spriteData );
				static SpriteViewRef create( SpriteDataXml& spriteData );

				po::SpritesheetRef& getSpritesheet() { return mSpritesheet; }
				po::SpritesheetAnimationRef& getAnimation() { return mSpritesheetAnimation; }
				ci::Rectf getBounds() { return mSpritesheet->getOriginalBounds(); }
				void setReplacementColor( ci::Color color );

				bool pointInside( const ci::vec2& point, bool localize = true );

			protected:
				SpriteView();

				void setup( ci::gl::TextureRef texture, ci::JsonTree json );
				void setup( ci::gl::TextureRef texture, ci::XmlTree xml );

				void setup( std::vector<ci::gl::TextureRef>& textures, std::vector<ci::JsonTree>& data );
				void setup( std::vector<ci::gl::TextureRef>& textures, std::vector<ci::XmlTree>& data );
				void setup( po::SpritesheetRef spriteSheet );
				void update();
				void draw();

			private:
				ci::gl::GlslProgRef mShader;
				bool mIsKeyShaderEnabled;
				ci::Color mReplacementColor;

				po::SpritesheetRef mSpritesheet;
				po::SpritesheetAnimationRef mSpritesheetAnimation;

				void setupAnimation();

		};
	}
}
