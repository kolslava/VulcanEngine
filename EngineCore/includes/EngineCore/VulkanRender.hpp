
typedef struct VkInstance_T* VkInstance;

namespace EngineCore {

	class VulkanRender {
	public:
		VulkanRender();
		virtual ~VulkanRender();

		void Init();
		void Render();
		void Cleanup();

	private:
		void CreateInstance();

	private:
		VkInstance m_pInstance;
	};

}