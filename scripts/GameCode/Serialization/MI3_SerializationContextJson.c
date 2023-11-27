
// Convenience Save/Load contexts to work with json format

/*-----------------------------------------------------------
 Context to save data to given serliazation container
*/
modded class SCR_JsonSaveContext : ContainerSerializationSaveContext
{
	void SCR_JsonSaveContext(bool skipEmptyObjects = true)
	{
		container = new JsonSaveContainer();
		container.SetMaxDecimalPlaces(3);
		SetContainer(container);
	}

	void ~SCR_JsonSaveContext()
	{
	}
};
