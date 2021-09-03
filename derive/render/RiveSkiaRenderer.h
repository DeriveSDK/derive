#pragma once

/**
 * @file RiveSkiaRenderer.h
 * Based on the skia renderer supplied with Rive-cpp, with only
 * minor changes to support some native Derive types.
 */

// Derive
#include "derive/geom/Matrix.h"
// Skia
#include "core/SkCanvas.h"
#include "core/SkPaint.h"
#include "core/SkPath.h"
// Rive
#include "rive/renderer.hpp"
// Other
#include <vector>

using namespace rive;
using namespace derive::geom;

namespace derive {
	namespace render {

        class ToSkia {
        public:
            static SkMatrix convert(const rive::Mat2D& m) {
                SkMatrix skMatrix;
                skMatrix.set9((SkScalar[9])
                            // Skia Matrix is row major
                            {// Row 1
                            m[0],
                            m[2],
                            m[4],
                            // Row 2
                            m[1],
                            m[3],
                            m[5],
                            // Row 3
                            0.0,
                            0.0,
                            1.0});
                return skMatrix;
            }

            static SkPoint convert(const rive::Vec2D& point) {
                return SkPoint::Make(point[0], point[1]);
            }

            static SkPaint::Cap convert(rive::StrokeCap cap) {
                switch (cap) {
                    case rive::StrokeCap::butt:
                        return SkPaint::Cap::kButt_Cap;
                    case rive::StrokeCap::round:
                        return SkPaint::Cap::kRound_Cap;
                    case rive::StrokeCap::square:
                        return SkPaint::Cap::kSquare_Cap;
                }
                return SkPaint::Cap::kButt_Cap;
            }

            static SkPaint::Join convert(rive::StrokeJoin join) {
                switch (join) {
                    case rive::StrokeJoin::bevel:
                        return SkPaint::Join::kBevel_Join;
                    case rive::StrokeJoin::round:
                        return SkPaint::Join::kRound_Join;
                    case rive::StrokeJoin::miter:
                        return SkPaint::Join::kMiter_Join;
                }
                return SkPaint::Join::kMiter_Join;
            }

            static SkBlendMode convert(rive::BlendMode blendMode) {
                switch (blendMode) {
                    case rive::BlendMode::srcOver:
                        return SkBlendMode::kSrcOver;
                    case rive::BlendMode::screen:
                        return SkBlendMode::kScreen;
                    case rive::BlendMode::overlay:
                        return SkBlendMode::kOverlay;
                    case rive::BlendMode::darken:
                        return SkBlendMode::kDarken;
                    case rive::BlendMode::lighten:
                        return SkBlendMode::kLighten;
                    case rive::BlendMode::colorDodge:
                        return SkBlendMode::kColorDodge;
                    case rive::BlendMode::colorBurn:
                        return SkBlendMode::kColorBurn;
                    case rive::BlendMode::hardLight:
                        return SkBlendMode::kHardLight;
                    case rive::BlendMode::softLight:
                        return SkBlendMode::kSoftLight;
                    case rive::BlendMode::difference:
                        return SkBlendMode::kDifference;
                    case rive::BlendMode::exclusion:
                        return SkBlendMode::kExclusion;
                    case rive::BlendMode::multiply:
                        return SkBlendMode::kMultiply;
                    case rive::BlendMode::hue:
                        return SkBlendMode::kHue;
                    case rive::BlendMode::saturation:
                        return SkBlendMode::kSaturation;
                    case rive::BlendMode::color:
                        return SkBlendMode::kColor;
                    case rive::BlendMode::luminosity:
                        return SkBlendMode::kLuminosity;
                }
                return SkBlendMode::kSrcOver;
            }
        };

        class SkiaRenderPath : public RenderPath{
        private:
            SkPath m_Path;

        public:
            const SkPath& path() const { return m_Path; }
            void reset() override;
            void addRenderPath(RenderPath* path, const Mat2D& transform) override;
            void fillRule(FillRule value) override;
            void moveTo(float x, float y) override;
            void lineTo(float x, float y) override;
            void cubicTo( float ox, float oy, float ix, float iy, float x, float y ) override;
            virtual void close() override;
        };

        struct GradientStop {
            unsigned int color;
            float stop;
            GradientStop(unsigned int color, float stop) : color(color), stop(stop) {}
        };

        class SkiaGradientBuilder{
        public:
            std::vector<GradientStop> stops;
            float sx, sy, ex, ey;
            virtual ~SkiaGradientBuilder() {}
            SkiaGradientBuilder(float sx, float sy, float ex, float ey) :
                sx(sx), sy(sy), ex(ex), ey(ey) { }
            virtual void make(SkPaint& paint) = 0;
        };

        class SkiaRadialGradientBuilder : public SkiaGradientBuilder {
        public:
            SkiaRadialGradientBuilder(float sx, float sy, float ex, float ey) :
                SkiaGradientBuilder(sx, sy, ex, ey){}
            void make(SkPaint& paint) override;
        };

        class SkiaLinearGradientBuilder : public SkiaGradientBuilder {
        public:
            SkiaLinearGradientBuilder(float sx, float sy, float ex, float ey) :
                SkiaGradientBuilder(sx, sy, ex, ey)
            {
            }
            void make(SkPaint& paint) override;
        };

        class SkiaRenderPaint : public RenderPaint {
        private:
            SkPaint m_Paint;
            SkiaGradientBuilder* m_GradientBuilder;

        public:
            const SkPaint& paint() const { return m_Paint; }
            SkiaRenderPaint();
            void style(RenderPaintStyle style) override;
            void color(unsigned int value) override;
            void thickness(float value) override;
            void join(StrokeJoin value) override;
            void cap(StrokeCap value) override;
            void blendMode(BlendMode value) override;

            void linearGradient(float sx, float sy, float ex, float ey) override;
            void radialGradient(float sx, float sy, float ex, float ey) override;
            void addStop(unsigned int color, float stop) override;
            void completeGradient() override;
        };

		/**
		 * @brief A renderer to render rive objects to Skia
		 */
		class RiveSkiaRenderer : public Renderer {
		public:
			SkCanvas* canvas;
            SkMatrix* transformMatrix;

			RiveSkiaRenderer( SkCanvas* c );
            ~RiveSkiaRenderer();
			void save() override;
			void restore() override;
			void transform( const Mat2D& transform ) override;
			void transform( Matrix* transform );
			void drawPath( RenderPath* path, RenderPaint* paint ) override;
			void clipPath( RenderPath* path ) override;
		};

	} // render
} // derive