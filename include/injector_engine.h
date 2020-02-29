#pragma once
#include <set>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>

// Minimum OpenGL Version = 3.3

namespace Injector
{
	class Entity
	{
	public:
		std::string name;

		Entity(std::string name = "UntitledEntity");

		virtual void OnUpdate();
		virtual void OnWindowClose(GLFWwindow* window);
		virtual void OnWindowSize(GLFWwindow* window, int width, int height);
		virtual void OnFramebufferSize(GLFWwindow* window, int width, int height);
		virtual void OnWindowContentScale(GLFWwindow* window, float xscale, float yscale);
		virtual void OnWindowPosition(GLFWwindow* window, int xpos, int ypos);
		virtual void OnWindowIconify(GLFWwindow* window, int iconified);
		virtual void OnWindowMaximize(GLFWwindow* window, int iconified);
		virtual void OnWindowFocus(GLFWwindow* window, int focused);
		virtual void OnWindowRefresh(GLFWwindow* window);
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
	protected:
		static GLuint CreateShader(Type type);
		static void DeleteShader(GLuint shader);
	public:
		const GLuint shader;
		const Type type;

		Shader(Type type, const std::string& source, bool readFromFile);
		~Shader();
	};

	class Material
	{
	protected:
		static GLuint CreateProgram();
		static void DeleteProgram(GLuint program);

		static void AttachShader(GLuint program, GLuint shader);
		static void DetachShader(GLuint program, GLuint shader);

		static void LinkProgram(GLuint program);

		static GLuint GetUniformLocation(GLuint program, const std::string& name);
		GLuint GetUniform(const std::string& name) const;

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

		void UseProgram() const;
		static void UnuseProgram();

		virtual void OnRender(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj) const = 0;
	};

	class AmbientMaterial : public Material
	{
	public:
		const GLint mvp;
		const GLint color;

		AmbientMaterial(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

		void SetMVP(const glm::mat4& value) const;
		void SetColor(const glm::vec4& value) const;

		void OnRender(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj) const override;
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

		void OnRender(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj) const override;
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
		enum class Usage : GLenum
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
		Usage usage;
		GLsizeiptr size;

		static GLuint GenerateBuffer();
		static void DeleteBuffer(GLuint buffer);
	public:
		const GLuint buffer;
		const Type type;

		Buffer(Type type, Usage usage, GLsizeiptr size = 0, const GLvoid* data = nullptr);
		~Buffer();

		Usage GetUsage();
		GLsizeiptr GetSize();

		void BindBuffer() const;
		void UnbindBuffer() const;

		void SetBufferData(GLsizeiptr size = 0, const GLvoid* data = nullptr);
		void Buffer::SetBufferData(Usage usage, GLsizeiptr size = 0, const GLvoid* data = nullptr);

		void SetBufferSubData(GLintptr offset, GLsizeiptr size, const GLvoid* data);
	};

	class VertexArray
	{
	protected:
		static GLuint GenerateVertexArray();
		static void DeleteVertexArray(GLuint vertexArray);
	public:
		const GLuint vertexArray;

		VertexArray();
		~VertexArray();

		void BindVertexArray() const;
		static void UnbindVertexArray();
	};

	class VertexAttribute
	{
	public:
		enum class Type : GLenum
		{
			Byte = GL_BYTE,
			UnsignedByte = GL_UNSIGNED_BYTE,
			Short = GL_SHORT,
			UnsignedShort = GL_UNSIGNED_SHORT,
			Int = GL_INT,
			UnsignedInt = GL_UNSIGNED_INT,
			HalfFloat = GL_HALF_FLOAT,
			Float = GL_FLOAT,
			Double = GL_DOUBLE,
			Fixed = GL_FIXED,
			Int_2_10_10_10_Rev = GL_INT_2_10_10_10_REV,
			UnsignedInt_2_10_10_10_Rev = GL_UNSIGNED_INT_2_10_10_10_REV,
			UnsignedInt_10f_11f_11f_Rev = GL_UNSIGNED_INT_10F_11F_11F_REV, // GL 4.4
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
		static const std::vector<GLfloat> TriangleVertices;
		static const std::vector<GLfloat> TriangleNormals;
		static const std::vector<GLbyte> TriangleIndices;

		static const std::vector<GLfloat> SquareVertices;
		static const std::vector<GLfloat> SquareNormals;
		static const std::vector<GLbyte> SquareIndices;

		static const std::vector<GLfloat> CubeVertices;
		static const std::vector<GLfloat> CubeNormals;
		static const std::vector<GLbyte> CubeIndices;
	};

	class Mesh : public VertexArray
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

		template<class TVertex, class TIndex>
		static std::shared_ptr<Mesh> Create(DrawMode drawMode, IndexType indexType, Buffer::Usage usage, const std::vector<TVertex>& vertices, const std::vector<TIndex>& indices, const std::vector<VertexAttribute>& vertexAttributes);

		static std::shared_ptr<Mesh> CreateTriangleV(DrawMode drawMode = DrawMode::Triangles, Buffer::Usage usage = Buffer::Usage::StaticDraw);
		static std::shared_ptr<Mesh> CreateSquareV(DrawMode drawMode = DrawMode::Triangles, Buffer::Usage usage = Buffer::Usage::StaticDraw);
		static std::shared_ptr<Mesh> CreateCubeV(DrawMode drawMode = DrawMode::Triangles, Buffer::Usage usage = Buffer::Usage::StaticDraw);

		static std::shared_ptr<Mesh> CreateTriangleVN(DrawMode drawMode = DrawMode::Triangles, Buffer::Usage usage = Buffer::Usage::StaticDraw);
		static std::shared_ptr<Mesh> CreateSquareVN(DrawMode drawMode = DrawMode::Triangles, Buffer::Usage usage = Buffer::Usage::StaticDraw);
		static std::shared_ptr<Mesh> CreateCubeVN(DrawMode drawMode = DrawMode::Triangles, Buffer::Usage usage = Buffer::Usage::StaticDraw);
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

		// TODO: add getters

		GLFWimage GetGLFW();
	};

	class Renderer : public Entity, public Transform
	{
	public:
		std::shared_ptr<Material> material;
		std::shared_ptr<Mesh> mesh;

		Renderer(std::shared_ptr<Material> material, std::shared_ptr<Mesh> mesh);

		virtual void OnRender(const glm::mat4& view, const glm::mat4& proj, const glm::mat4& viewProj);
	};

	class Camera : public Entity, public Transform
	{
	protected:
		glm::mat4 projMatrix;
		glm::mat4 viewProjMatrix;

		bool isProjMatrixChaged;
		bool isViewProjMatrixChaged;

		std::set<std::shared_ptr<Renderer>> renderers; // TODO: try make const
	public:
		Camera();

		void SetProjMatrixChanged();
		void SetViewProjMatrixChanged();

		glm::mat4 GetMatrix() override;
		virtual glm::mat4 GetProjMatrix() = 0;
		virtual glm::mat4 GetViewProjMatrix();

		void OnUpdate() override;

		void AddRenderer(std::shared_ptr<Renderer> renderer);
		void RemoveRenderer(std::shared_ptr<Renderer> renderer);
	};

	class PerspCamera : public Camera
	{
	public:
		float fieldOfView;
		float aspectRatio;
		float nearClipPlane;
		float farClipPlane;

		PerspCamera(float fieldOfView = 45.0f, float aspectRatio = 4.0f / 3.0f, float nearClipPlane = 0.01f, float farClipPlane = 1000.0f);

		void OnFramebufferSize(GLFWwindow* window, int width, int height) override;
		glm::mat4 GetProjMatrix() override;
	};

	class Engine
	{
	protected:
		static bool isInitialized;

		static double time;
		static double lastTime;
		static double deltaTime;

		static bool cullFace;
		static bool depthTest;

		static GLFWwindow* mainWindow;
		static std::set<std::shared_ptr<Entity>> entities;

		static std::shared_ptr<AmbientMaterial> ambientMaterial;
		static std::shared_ptr<DiffuseMaterial> diffuseMaterial;

		static std::shared_ptr<Mesh> triangleMeshV;
		static std::shared_ptr<Mesh> squareMeshV;
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
	public:
		static bool IsInitialized();
		static void Initialize();
		static void Terminate();
		static void Start();

		static std::string ReadTextFromFile(const std::string& filePath);

		static double GetTime();
		static double GetLastTime();
		static double GetDeltaTime();

		static bool GetCullFace();
		static void SetCullFace(bool value);

		static bool GetDepthTest();
		static void SetDepthTest(bool value);

		static void AddEntity(std::shared_ptr<Entity> entity);
		static void RemoveEntity(std::shared_ptr<Entity> entity);

		static std::shared_ptr<AmbientMaterial> GetAmbientMaterial();
		static std::shared_ptr<DiffuseMaterial> GetDiffuseMaterial();

		static std::shared_ptr<Mesh> GetTriangleMeshV();
		static std::shared_ptr<Mesh> GetSquareMeshV();
		static std::shared_ptr<Mesh> GetCubeMeshV();
		static std::shared_ptr<Mesh> GetCubeMeshVN();
	};
}
