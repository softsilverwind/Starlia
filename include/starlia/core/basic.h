#ifndef __BASIC_H__
#define __BASIC_H__

#include "layer.h"
#include "structs.h"

#define POINTS 256
#define step (2 * M_PI / POINTS)

namespace Starlia
{

class SClearColorLayer : public SLayer
{
	private:
		Color3f color;

	public:
		SClearColorLayer(Color3f);

		virtual void draw() override;
};

class SClearDepthLayer : public SLayer
{
	public:
		SClearDepthLayer();

		virtual void draw() override;
};

class SStaticShaderLayer : public SListLayer<SObject>
{
	private:
		unsigned linked_program;

	protected:
		shared_ptr<SCamera> camera;

		virtual void draw() override;

		virtual unsigned int getActiveProgram() override;

	public:
		SStaticShaderLayer(shared_ptr<SCamera> camera, const string& f_shader, const string& v_shader);
		SStaticShaderLayer(SCamera *camera, const string& f_shader, const string& v_shader);

		shared_ptr<SCamera> getCamera();
};

class SBasicColorLayer : public SStaticShaderLayer
{
	private:
		static const string v_shader;
		static const string f_shader;

	public:
		SBasicColorLayer(shared_ptr<SCamera> camera) : SStaticShaderLayer(camera, v_shader, f_shader) {};
		SBasicColorLayer(SCamera *camera = new SOrthoCamera(Coord2f(0, 0), Coord2f(1, 1))) : SBasicColorLayer(shared_ptr<SCamera>(camera)) {};
};

class SBasicObjectLayer : public SStaticShaderLayer
{
	private:
		static const string v_shader;
		static const string f_shader;

	public:
		SBasicObjectLayer(shared_ptr<SCamera> camera) : SStaticShaderLayer(camera, v_shader, f_shader) {};
		SBasicObjectLayer(SCamera *camera = new SOrthoCamera(Coord2f(0, 0), Coord2f(1, 1))) : SBasicObjectLayer(shared_ptr<SCamera>(camera)) {};
};

class SCircle : public SModel
{
	private:
		static bool initialized;
		static vector<Coord2f> vertices;

		static void initialize();

		Color3f color;

	public:
		SCircle(Color3f color);

		virtual void draw(SLayer *) override;
};

}

#endif
