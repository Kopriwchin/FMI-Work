namespace LabelsApp.Transformations;

public class CensorTransformationFactory
{
    private readonly Dictionary<string, CensorTransformation> _cache = [];

    public CensorTransformation GetCensorTransformation(string word)
    {
        if (word.Length <= 4)
        {
            if (_cache.ContainsKey(word))
            {
                Console.WriteLine($"[Factory] Returning cached instance for '{word}'");
                return _cache[word];
            }

            Console.WriteLine($"[Factory] Creating and caching new instance for '{word}'");
            var flyweight = new CensorTransformation(word);
            _cache[word] = flyweight;
            return flyweight;
        }

        Console.WriteLine($"[Factory] Word '{word}' is too long. Creating new instance.");
        return new CensorTransformation(word);
    }
}