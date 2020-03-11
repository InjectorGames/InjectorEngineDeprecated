#pragma once
#include <set>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

#ifndef NDEBUG
#include <glad/glad_debug.h>
#else
#include <glad/glad_release.h>
#endif

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

// Minimum OpenGL Version = 3.3

namespace Injector
{
	static std::string ReadTextFromFile(const std::string& filePath)
	{
		std::ifstream ifs(filePath);

		if (!ifs)
			throw std::runtime_error("Failed to open text file.");

		ifs.seekg(0, std::ios::end);
		size_t size = ifs.tellg();
		ifs.seekg(0, std::ios::beg);
		std::string buffer(size, ' ');
		ifs.read(&buffer[0], size);
		return buffer;
	}
	static std::vector<unsigned char> ReadBytesFromFile(const std::string& filePath)
	{
		std::ifstream ifs(filePath);

		if (!ifs)
			throw std::runtime_error("Failed to open binary file.");

		ifs.seekg(0, std::ios::end);
		size_t size = ifs.tellg();
		ifs.seekg(0, std::ios::beg);
		std::vector<unsigned char> buffer(size);
		ifs.read((char*)&buffer[0], size);
		return buffer;
	}

	class Entity
	{
	public:
		std::string name;

		Entity(std::string name = "UntitledEntity");

		virtual void OnUpdate(double time, double deltaTime);
		virtual void OnWindowClose(GLFWwindow* window);
		virtual void OnWindowSize(GLFWwindow* window, int width, int height);
		virtual void OnFramebufferSize(GLFWwindow* window, int width, int height);
		virtual void OnWindowContentScale(GLFWwindow* window, float xscale, float yscale);
		virtual void OnWindowPosition(GLFWwindow* window, int xpos, int ypos);
		virtual void OnWindowIconify(GLFWwindow* window, int iconified);
		virtual void OnWindowMaximize(GLFWwindow* window, int iconified);
		virtual void OnWindowFocus(GLFWwindow* window, int focused);
		virtual void OnWindowRefresh(GLFWwindow* window);
		virtual void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};

	class Transform
	{
	protected:
		glm::mat4 matrix;
		bool isMatrixChaged;
	public:
		glm::vec3 position;
		glm::quat rotation;
		glm::vec3 scale;

		Transform(glm::vec3 position = glm::vec3(0.0f), glm::quat rotation = glm::quat(glm::vec3(0.0f)), glm::vec3 scale = glm::vec3(1.0f));

		void Translate(glm::vec3 offset);
		void Rotate(glm::quat offset);

		void SetMatrixChanged();
		virtual glm::mat4 GetMatrix();
	};

	class Camera : public Entity, public Transform
	{
	protected:
		glm::mat4 projMatrix;
		glm::mat4 viewProjMatrix;

		bool isProjMatrixChaged;
		bool isViewProjMatrixChaged;
	public:
		Camera();

		void SetProjMatrixChanged();
		void SetViewProjMatrixChanged();

		virtual glm::mat4 GetProjMatrix();
		virtual glm::mat4 GetViewProjMatrix();
	};

	class PerspectiveCamera : public Camera
	{
	public:
		float fieldOfView;
		float aspectRatio;
		float nearClipPlane;
		float farClipPlane;

		PerspectiveCamera(float fieldOfView = 45.0f, float aspectRatio = 4.0f / 3.0f, float nearClipPlane = 0.01f, float farClipPlane = 1000.0f);

		void OnFramebufferSize(GLFWwindow* window, int width, int height) override;
		glm::mat4 GetProjMatrix() override;
	};

	class FreeLookCamera : public PerspectiveCamera
	{
	public:
		void OnUpdate(double time, double deltaTime) override;
	};

	class Window
	{
	public:
		enum class CullType
		{
			Front,
			Back,
			Both,
		};
		enum class BlendType
		{
			Zero,
			One,
			SrcColor,
			OneMinusSrcColor,
			DstColor,
			OneMinusDstColor,
			SrcAlpha,
			OneMinusSrcAlpha,
			DstAlpha,
			OneMinusDstAlpha,
			ConstColor,
			OneMinusConstColor,
			ConstAlpha,
			OneMinusConstAlpha,
			SrcAlphaSaturate,
			Src1Color,
			OneMinusSrc1Color,
			Src1Alpha,
			OneMinusSrc1Alpha,
		};
	protected:
		bool windigOrder;
		bool faceCulling;
		bool depthTesting;
		bool stencilTesting;
		bool colorBlending;

		virtual GLFWwindow* CreateWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	public:
		GLFWwindow* const window;

		Window(int width = 800, int height = 600, const std::string& title = "Untitled Window", GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~Window();

		void SetWindowIcon(const std::vector<GLFWimage>& icons) const;

		void MakeContextCurrent() const;
		static void DetachContextCurrent();

		virtual void ClearBuffers() = 0;

		bool GetFaceCullingFlag();
		bool GetDepthTestFlag();
		bool GetStencilTestFlag();
		bool GetBlendFlag();

		virtual void SetWindingOrder(bool clockwise) = 0;
		virtual void SetFaceCulling(bool value) = 0;
		virtual void SetDepthTesting(bool value) = 0;
		virtual void SetStencilTesting(bool value) = 0;
		virtual void SetColorBlending(bool value) = 0;
		
		virtual void SetFaceCullType(CullType type) = 0;
		virtual void SetColorBlendType(BlendType source, BlendType destination) = 0;
		virtual void SetColorBlendType(BlendType sourceColor, BlendType destinationColor, BlendType sourceAlpha, BlendType destinationAlpha) = 0;
	};

	class OpenGLWindow : public Window
	{
	protected:
		GLFWwindow* CreateWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) override;

		static GLenum BlendTypeToEnum(BlendType type);
	public:
		OpenGLWindow(int width = 800, int height = 600, const std::string& title = "OpenGL Window", GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

		void ClearBuffers() override;

		void SetWindingOrder(bool clockwise) override;
		void SetFaceCulling(bool value) override;
		void SetDepthTesting(bool value) override;
		void SetStencilTesting(bool value) override;
		void SetColorBlending(bool value) override;

		void SetFaceCullType(CullType type) override;
		void SetColorBlendType(BlendType source, BlendType destination) override;
		void SetColorBlendType(BlendType sourceColor, BlendType destinationColor, BlendType sourceAlpha, BlendType destinationAlpha) override;
	};

	class VulkanWindow : public Window
	{
		// TODO: 
	};

	class Texture
	{
	public:
		enum class Type : GLenum
		{
			Texture1D = GL_TEXTURE_1D,
			Texture2D = GL_TEXTURE_2D,
			Texture3D = GL_TEXTURE_3D,
			Array1D = GL_TEXTURE_1D_ARRAY,
			Array2D = GL_TEXTURE_2D_ARRAY,
			Rectangle = GL_TEXTURE_RECTANGLE,
			CubeMap = GL_TEXTURE_CUBE_MAP,
			CubeMapArray = GL_TEXTURE_CUBE_MAP_ARRAY,
			Buffer = GL_TEXTURE_BUFFER,
			Multisample2D = GL_TEXTURE_2D_MULTISAMPLE, // GL 3.2
			MultisampleArray2D = GL_TEXTURE_2D_MULTISAMPLE_ARRAY, // GL 3.2
		};
	protected:
		static GLuint Generate();
	public:
		const GLuint texture;
		const Type type;

		Texture(Type type);
		~Texture();

		void Bind() const;
		void Unbind() const;

		void Activate(GLint index) const;
	};

	class Texture2D : public Texture
	{
	public:
		enum class ImageType : GLenum
		{
			Texture2D = GL_TEXTURE_2D,
			Proxy2D = GL_PROXY_TEXTURE_2D,
			Array1D = GL_TEXTURE_1D_ARRAY,
			ProxyArray1D = GL_PROXY_TEXTURE_1D_ARRAY,
			Rectangle = GL_TEXTURE_RECTANGLE,
			ProxyRectangle = GL_PROXY_TEXTURE_RECTANGLE,
			CubeMapPositiveX = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			CubeMapNegativeX = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			CubeMapPositiveY = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			CubeMapNegativeY = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			CubeMapPositiveZ = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			CubeMapNegativeZ = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
			ProxyCubeMap = GL_PROXY_TEXTURE_CUBE_MAP,
		};
		enum class InternalFormatType : GLenum
		{
			DepthComponent = GL_DEPTH_COMPONENT,
			DepthStencil = GL_DEPTH_STENCIL,
			Red = GL_RED,
			RG = GL_RG,
			RGB = GL_RGB,
			RGBA = GL_RGBA,

			// TODO: add other sized and compressed formats
			// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexImage2D.xhtml
		};
		enum class FormatType : GLenum
		{
			Red = GL_RED,
			RG = GL_RG,
			RGB = GL_RGB,
			BGR = GL_BGR,
			RGBA = GL_RGBA,
			BGRA = GL_BGRA,
			RedInteger = GL_RED_INTEGER,
			RGInteger = GL_RG_INTEGER,
			RGBInteger = GL_RGB_INTEGER,
			BGRInteger = GL_BGR_INTEGER,
			RGBAInteger = GL_RGBA_INTEGER,
			BGRAInteger = GL_BGRA_INTEGER,
			StencilIndex = GL_STENCIL_INDEX,
			DepthComponent = GL_DEPTH_COMPONENT,
			DepthStencil = GL_DEPTH_STENCIL,
		};
		enum class PixelType : GLenum
		{
			Unyte = GL_UNSIGNED_BYTE,
			Byte = GL_BYTE,
			Ushort = GL_UNSIGNED_SHORT,
			Short = GL_SHORT,
			Uint = GL_UNSIGNED_INT,
			Int = GL_INT,
			Hfloat = GL_HALF_FLOAT,
			Float = GL_FLOAT,
			Ubyte_3_3_2 = GL_UNSIGNED_BYTE_3_3_2,
			Ubyte_2_3_3_Rev = GL_UNSIGNED_BYTE_2_3_3_REV,
			Ushort_5_6_5 = GL_UNSIGNED_SHORT_5_6_5,
			Ushort_5_6_5_Rev = GL_UNSIGNED_SHORT_5_6_5_REV,
			Ushort_4_4_4_4 = GL_UNSIGNED_SHORT_4_4_4_4,
			Ushort_4_4_4_4_Rev = GL_UNSIGNED_SHORT_4_4_4_4_REV,
			Ushort_5_5_5_1 = GL_UNSIGNED_SHORT_5_5_5_1,
			Ushort_1_5_5_5_Rev = GL_UNSIGNED_SHORT_1_5_5_5_REV,
			Uint_8_8_8_8 = GL_UNSIGNED_INT_8_8_8_8,
			Uint_8_8_8_8_Rev = GL_UNSIGNED_INT_8_8_8_8_REV,
			Uint_10_10_10_2 = GL_UNSIGNED_INT_10_10_10_2,
			Uint_2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
		};

		Texture2D(ImageType image, GLint level, InternalFormatType internalFormat, GLsizei width, GLsizei height, FormatType format, PixelType pixel, const GLvoid* data, bool generateMipmap);
	};

	class Shader
	{
	public:
		enum class Type : GLenum
		{
			Vertex = GL_VERTEX_SHADER, // GL 2.0
			Fragment = GL_FRAGMENT_SHADER, // GL 2.0
			Geometry = GL_GEOMETRY_SHADER, // GL 3.2
			Compute = GL_COMPUTE_SHADER, // GL 4.2
			TessControl = GL_TESS_CONTROL_SHADER, // GL 4.0
			TessEvaluation = GL_TESS_EVALUATION_SHADER, // GL 4.0
		};

		const GLuint shader;
		const Type type;

		Shader(Type type, const std::string& source, bool readFromFile);
		~Shader();
	};

	class Material
	{
	protected:


		void Attach(GLuint shader) const;
		void Detach(GLuint shader) const;

		void Link() const;

		GLuint GetUniformLocation(const std::string& name) const;

		static void SetUniform(GLint index, GLint value);
		static void SetUniform(GLint index, GLfloat value);
		static void SetUniform(GLint index, const glm::vec2& value);
		static void SetUniform(GLint index, const glm::vec3& value);
		static void SetUniform(GLint index, const glm::vec4& value);
		static void SetUniform(GLint index, const glm::mat2& value);
		static void SetUniform(GLint index, const glm::mat3& value);
		static void SetUniform(GLint index, const glm::mat4& value);
	public:
		const GLuint program;

		Material(std::shared_ptr<Shader> shader);
		Material(std::shared_ptr<Shader> shader1, std::shared_ptr<Shader> shader2);
		Material(std::shared_ptr<Shader> shader1, std::shared_ptr<Shader> shader2, std::shared_ptr<Shader> shader3);

		~Material();

		void Use() const;
		static void Release();

		virtual void OnRender(std::shared_ptr<Window> window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj);
	};

	class ColorMaterial : public Material
	{
	public:
		const GLint mvp;
		const GLint color;

		ColorMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

		void SetMVP(const glm::mat4& value) const;
		void SetColor(const glm::vec4& value) const;

		void OnRender(std::shared_ptr<Window> window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj) override;
	};

	class ColorTexMaterial : public ColorMaterial
	{
	public:
		const GLint textureMap;
		std::shared_ptr<Texture2D> texture;

		ColorTexMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

		void OnRender(std::shared_ptr<Window> window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj) override;
	};

	class DiffuseMaterial : public Material
	{
	public:
		const GLint mvp;
		const GLint normal;
		const GLint color;
		const GLint ambientColor;
		const GLint lightColor;
		const GLint lightDirection;

		DiffuseMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

		void SetMVP(const glm::mat4& value) const;
		void SetNormal(const glm::mat3& value) const;
		void SetColor(const glm::vec4& value) const;
		void SetAmbientColor(const glm::vec4& value) const;
		void SetLightColor(const glm::vec4& value) const;
		void SetLightDirection(const glm::vec3& value) const;

		void OnRender(std::shared_ptr<Window> window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj) override;
	};

	class EditorMaterial : public Material
	{
	public:
		const GLint model;
		const GLint color;

		EditorMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

		void SetModel(const glm::mat4& value) const;
		void SetColor(const glm::vec4& value) const;

		void OnRender(std::shared_ptr<Window> window, const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj) override;
	};

	class Buffer
	{
	public:
		enum class Type : GLenum
		{
			Array = GL_ARRAY_BUFFER, // GL 2.0
			AtomicCounter = GL_ATOMIC_COUNTER_BUFFER, // GL 4.3
			CopyRead = GL_COPY_READ_BUFFER, // GL 3.1
			CopyWrite = GL_COPY_WRITE_BUFFER, // GL 2.0
			DispatchIndirect = GL_DISPATCH_INDIRECT_BUFFER, // GL 4.3
			DrawIndirect = GL_DRAW_INDIRECT_BUFFER, // GL 2.0
			ElementArray = GL_ELEMENT_ARRAY_BUFFER, // GL 2.0
			PixelPack = GL_PIXEL_PACK_BUFFER, // GL 2.0
			PixelUnpack = GL_PIXEL_UNPACK_BUFFER, // GL 2.0
			Query = GL_QUERY_BUFFER, // GL 4.4
			ShaderStorage = GL_SHADER_STORAGE_BUFFER, // GL 4.3
			Texture = GL_TEXTURE_BUFFER, // GL 3.1
			TransformFeedback = GL_TRANSFORM_FEEDBACK_BUFFER, // GL 2.0
			Uniform = GL_UNIFORM_BUFFER, // GL 3.1
		};
		enum class UsageType : GLenum
		{
			// STREAM: The data store contents will be modified once and used at most a few times.
			// STATIC: The data store contents will be modified once and used many times.
			// DYNAMIC: The data store contents will be modified repeatedly and used many times.

			// DRAW: The data store contents are modified by the application, and used as the source for GL drawing and image specification commands.
			// READ: The data store contents are modified by reading data from the GL, and used to return that data when queried by the application.
			// COPY: The data store contents are modified by reading data from the GL, and used as the source for GL drawing and image specification commands.

			StreamDraw = GL_STREAM_DRAW,
			StreamRead = GL_STREAM_READ,
			StreamCopy = GL_STREAM_COPY,
			StaticDraw = GL_STATIC_DRAW,
			StaticRead = GL_STATIC_READ,
			StaticCopy = GL_STATIC_COPY,
			DynamicDraw = GL_DYNAMIC_DRAW,
			DynamicRead = GL_DYNAMIC_READ,
			DynamicCopy = GL_DYNAMIC_COPY,
		};
	protected:
		UsageType usage;
		GLsizeiptr size;

		static GLuint Generate();
	public:
		const GLuint buffer;
		const Type type;

		Buffer(Type type, UsageType usage, GLsizeiptr size = 0, const GLvoid* data = nullptr);
		~Buffer();

		UsageType GetUsage();
		GLsizeiptr GetSize();

		void Bind() const;
		void Unbind() const;

		void SetData(GLsizeiptr size = 0, const GLvoid* data = nullptr);
		void SetData(UsageType usage, GLsizeiptr size = 0, const GLvoid* data = nullptr);

		void SetSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data);
	};

	class Batch
	{
	protected:
		static GLuint Generate();
	public:
		const GLuint vertexArray;

		Batch();
		~Batch();

		void Bind() const;
		static void Unbind();
	};

	class VertexAttribute
	{
	public:
		enum class Type : GLenum
		{
			Byte = GL_BYTE,
			Ubyte = GL_UNSIGNED_BYTE,
			Short = GL_SHORT,
			Ushort = GL_UNSIGNED_SHORT,
			Int = GL_INT,
			Uint = GL_UNSIGNED_INT,
			Hfloat = GL_HALF_FLOAT,
			Float = GL_FLOAT,
			Double = GL_DOUBLE,
			Fixed = GL_FIXED,
			Int_2_10_10_10_Rev = GL_INT_2_10_10_10_REV,
			Uint_2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
			Uint_10f_11f_11f_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV, // GL 4.4
		};
		enum class Size : GLint
		{
			One = 1,
			Two = 2,
			Three = 3,
			Four = 4,
		};

		const GLuint index;
		const Size size;
		const Type type;
		const bool normalized;
		const GLsizei stride;
		const GLintptr offset;

		VertexAttribute(GLuint index, Size size = Size::Four, Type type = Type::Float, bool normalized = false, GLsizei stride = 0, GLintptr offset = 0);

		void Enable() const;
		void Disable() const;
		void SetPointer() const;
	};

	class Primitive
	{
	public:
		static const std::vector<GLfloat> SquareVertices;
		static const std::vector<GLfloat> SquareNormals;
		static const std::vector<GLfloat> SquareTexCoords;
		static const std::vector<GLbyte> SquareIndices;

		static const std::vector<GLfloat> CubeVertices;
		static const std::vector<GLfloat> CubeNormals;
		static const std::vector<GLbyte> CubeIndices;
	};

	class Mesh : public Batch
	{
	public:
		enum class DrawMode : GLenum
		{
			Points = GL_POINTS,
			LineStrip = GL_LINE_STRIP,
			LineLoop = GL_LINE_LOOP,
			Lines = GL_LINES,
			LineStripAdjacency = GL_LINE_STRIP_ADJACENCY, // GL 3.2
			LinesAdjacency = GL_LINES_ADJACENCY, // GL 3.2
			TriangleStrip = GL_TRIANGLE_STRIP,
			TriangleFan = GL_TRIANGLE_FAN,
			Triangles = GL_TRIANGLES,
			TriangleStripAdjacency = GL_TRIANGLE_STRIP_ADJACENCY, // GL 3.2
			TrianglesAdjacency = GL_TRIANGLES_ADJACENCY, // GL 3.2
			Patches = GL_PATCHES,
		};
		enum class IndexType : GLenum
		{
			UnsignedByte = GL_UNSIGNED_BYTE,
			UnsignedShort = GL_UNSIGNED_SHORT,
			UnsignedInt = GL_UNSIGNED_INT,
		};

		const std::shared_ptr<Buffer> vertexBuffer;
		const std::shared_ptr<Buffer> indexBuffer;

		DrawMode drawMode;
		IndexType indexType;
		GLsizei indexCount;

		Mesh(DrawMode drawMode, IndexType indexType, GLsizei indexCount, std::shared_ptr<Buffer> vertexBuffer, std::shared_ptr<Buffer> indexBuffer, const std::vector<VertexAttribute>& vertexAttributes);

		void DrawElements();
		virtual void OnRender();
	};

	class Image
	{
	protected:
		int width;
		int height;
		int channels;

		unsigned char* data;
	public:
		Image(const std::string& filePath, int targetChannels = 0);
		~Image();

		int GetWidth();
		int GetHeight();
		int GetChannels();

		unsigned char* GetData();

		GLFWimage GetGLFW();
	};

	class Font
	{
	public:
		Font(const std::string& filePath, float pixelHeight);
		~Font();
	};

	class Renderer : public Entity, public Transform
	{
	public:
		bool isRenderable;
		std::shared_ptr<Material> material;
		std::shared_ptr<Mesh> mesh;

		Renderer(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh, bool isRenderable = true);

		virtual void OnRender(std::shared_ptr<Window> window, double time, double deltaTime, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj);
	};

	class EditorPanel : public Renderer
	{
	protected:
		float aspectRatio;
	public:

		EditorPanel(bool isRenderable = true);

		void OnFramebufferSize(GLFWwindow* window, int width, int height) override;
		glm::mat4 GetMatrix() override;
	};

	class Engine
	{
	public:
		enum class WindowType
		{
			Unknown,
			OpenGL,
			OpenGLES,
			Vulkan,
		};
	protected:
		static double lastTime;
		static float verticalAxis;
		static float horizontalAxis;

		static std::shared_ptr<Window> window;
		static std::set<std::shared_ptr<Entity>> entities;

		static std::shared_ptr<ColorMaterial> colorMaterial;
		static std::shared_ptr<ColorTexMaterial> colorTexMaterial;
		static std::shared_ptr<DiffuseMaterial> diffuseMaterial;
		static std::shared_ptr<EditorMaterial> editorMaterial;

		static std::shared_ptr<Mesh> squareMeshV;
		static std::shared_ptr<Mesh> squareMeshVN;
		static std::shared_ptr<Mesh> squareMeshVNU;
		static std::shared_ptr<Mesh> cubeMeshV;
		static std::shared_ptr<Mesh> cubeMeshVN;

		static void ErrorCallback(int error, const char* description);
		static void WindowCloseCallback(GLFWwindow* window);
		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
		static void WindowContentScaleCallback(GLFWwindow* window, float xscale, float yscale);
		static void WindowPosCallback(GLFWwindow* window, int xpos, int ypos);
		static void WindowIconifyCallback(GLFWwindow* window, int iconified);
		static void WindowMaximizeCallback(GLFWwindow* window, int maximized);
		static void WindowFocusCallback(GLFWwindow* window, int focused);
		static void WindowRefreshCallback(GLFWwindow* window);
		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void Clear();

		template<class TVertex, class TIndex>
		static std::shared_ptr<Mesh> CreateMesh(Mesh::DrawMode drawMode, Mesh::IndexType indexType, Buffer::UsageType usage, const std::vector<TVertex>& vertices, const std::vector<TIndex>& indices, const std::vector<VertexAttribute>& vertexAttributes);
	public:
		static std::shared_ptr<ColorMaterial> GetColorMaterial();
		static std::shared_ptr<ColorTexMaterial> GetColorTexMaterial();
		static std::shared_ptr<DiffuseMaterial> GetDiffuseMaterial();
		static std::shared_ptr<EditorMaterial> GetEditorMaterial();

		static std::shared_ptr<Mesh> GetSquareMeshV();
		static std::shared_ptr<Mesh> GetSquareMeshVN();

		static std::shared_ptr<Mesh> GetCubeMeshV();
		static std::shared_ptr<Mesh> GetCubeMeshVN();

		static void Initialize(WindowType windowType = WindowType::OpenGL);
		static void Terminate();

		static double GetLastTime();
		static float GetVerticalAxis();
		static float GetHorizontalAxis();

		static std::shared_ptr<Window> GetWindow();
		static void SwitchWindow(WindowType windowType);

		static void AddEntity(std::shared_ptr<Entity> entity);
		static void RemoveEntity(std::shared_ptr<Entity> entity);

		static void StartUpdate();
	};

	class DemoController : public Entity
	{
	protected:
		std::shared_ptr<Camera> camera;
		std::shared_ptr<Renderer> editor;
		std::shared_ptr<Renderer> cube;
	public:
		DemoController();

		void OnUpdate(double time, double deltaTime) override;
	};

	static void StartDemo()
	{
		Engine::Initialize();
		Engine::AddEntity(std::make_shared<DemoController>());
		Engine::StartUpdate();
		Engine::Terminate();
	}
}
